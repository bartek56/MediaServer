#include "alarmconfig.h"
#include <QtSystemd/sdmanager.h>
#include <QtSystemd/unit.h>

AlarmConfig::AlarmConfig(QObject *parent) : QObject(parent)
{
    auto state = Systemd::getUnitFileState(Systemd::System, ALARM_SERVICE);

    if(state.contains("able"))
        systemdAlarmSupport = true;
    else
    {
        qDebug() << "alarm systemd not support";
    }
}

void AlarmConfig::loadAlarmConfigurations(QObject *minVolumeSpinBox, QObject *maxVolumeSpinBox, QObject *defaultVolumeSpinBox, QObject *growingVolumeSpinBox, QObject *growingSpeedSpinBox,
                                          QObject *isNewestSongsListRadioButton, QObject *isPlaylistRadioButton, QObject *playlistComboBox)
{
    mAlarmConfigs = editAlarmConfigFile.LoadConfiguration();

    minVolumeSpinBox->setProperty("value", QVariant(mAlarmConfigs.at("minVolume")));
    maxVolumeSpinBox->setProperty("value", QVariant(mAlarmConfigs.at("maxVolume")));
    defaultVolumeSpinBox->setProperty("value", QVariant(mAlarmConfigs.at("defaultVolume")));
    growingVolumeSpinBox->setProperty("value", QVariant(mAlarmConfigs.at("growingVolume")));
    growingSpeedSpinBox->setProperty("value", QVariant(mAlarmConfigs.at("growingSpeed")));

    if(mAlarmConfigs.at("theNewestSongs") == "true")
    {
        isNewestSongsListRadioButton->setProperty("checked", QVariant(true));
        isPlaylistRadioButton->setProperty("checked", QVariant(false));
    }
    else
    {
        isNewestSongsListRadioButton->setProperty("checked", QVariant(false));
        isPlaylistRadioButton->setProperty("checked", QVariant(true));
    }

    QStringList mpdPlaylists = loadMPDPlaylists();
    playlistComboBox->setProperty("model", QVariant(mpdPlaylists));
    if(mpdPlaylists.count() == 0)
    {
        isNewestSongsListRadioButton->setProperty("checked", QVariant(true));
        isPlaylistRadioButton->setProperty("checked", QVariant(false));
    }
    else
    {
        int indexOfSavedPlaylist = mpdPlaylists.indexOf(mAlarmConfigs.at("playlist"));
        playlistComboBox->setProperty("currentIndex", QVariant(indexOfSavedPlaylist));
    }
}


QStringList AlarmConfig::loadMPDPlaylists()
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c"
                                        << "mpc lsplaylists | grep -v m3u");
    process.setReadChannel(QProcess::StandardOutput);
    QStringList musicPlayList;
    while(process.waitForFinished())
        ;
    while(process.canReadLine())
    {
        auto line = process.readLine();
        if(line.size() > 1)
        {
            line.remove(line.length() - 1, 1);
            QString qstrLine(line);
            musicPlayList.push_back(qstrLine);
        }
    }
    process.close();

    return musicPlayList;
}

bool AlarmConfig::checkAlarmIsActive()
{
    if(systemdAlarmSupport)
    {
        auto text = Systemd::loadUnit(Systemd::System, ALARM_TIMER)->activeState();
        return !text.contains("in");
    }
    else
    {
        return false;
    }
}

void AlarmConfig::checkAlarmService(QObject *enableAlarmSwitch)
{

    if(checkAlarmIsActive())
    {
        enableAlarmSwitch->setProperty("checked", QVariant(true));
    }
    else
    {
        enableAlarmSwitch->setProperty("checked", QVariant(false));
    }
}

void AlarmConfig::loadAlarmService(QObject *monCheckBox, QObject *tueCheckBox, QObject *wedCheckBox, QObject *thuCheckBox, QObject *friCheckBox, QObject *satCheckBox, QObject *sunCheckBox,
                                   QObject *timeHHSpinBox, QObject *timeMMSpinBox)
{
    QFile file(CONFIG_PATH + "/" + ALARM_TIMER);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString qstrLine(line);

        if(qstrLine.contains("OnCalendar"))
        {
            QString configLine = qstrLine;
            auto splitedString = configLine.split("=");
            auto configParameters = splitedString[1];

            auto splittedConfigParameters = configParameters.split(" ");
            auto daysOfWeek = splittedConfigParameters[0];

            if(daysOfWeek.contains("Mon"))
                monCheckBox->setProperty("checked", QVariant(true));
            if(daysOfWeek.contains("Tue"))
                tueCheckBox->setProperty("checked", QVariant(true));
            if(daysOfWeek.contains("Wed"))
                wedCheckBox->setProperty("checked", QVariant(true));
            if(daysOfWeek.contains("Thu"))
                thuCheckBox->setProperty("checked", QVariant(true));
            if(daysOfWeek.contains("Fri"))
                friCheckBox->setProperty("checked", QVariant(true));
            if(daysOfWeek.contains("Sat"))
                satCheckBox->setProperty("checked", QVariant(true));
            if(daysOfWeek.contains("Sun"))
                sunCheckBox->setProperty("checked", QVariant(true));

            auto time = splittedConfigParameters[1];
            auto timeSplitted = time.split(":");
            auto HH = timeSplitted[0];
            auto MM = timeSplitted[1];

            timeHHSpinBox->setProperty("value", QVariant(HH));
            timeMMSpinBox->setProperty("value", QVariant(MM));
        }
    }
    file.close();
}


void AlarmConfig::switchEnableAlarm_onClicked(const bool isEnable)
{
    if(systemdAlarmSupport)
    {
        if(isEnable)
        {
            Systemd::startUnit(Systemd::System, ALARM_TIMER, Systemd::Unit::Replace);
            Systemd::enableUnitFiles(Systemd::System, QStringList() << ALARM_TIMER, true, true);
        }
        else
        {
            Systemd::stopUnit(Systemd::System, ALARM_TIMER, Systemd::Unit::Replace);
            Systemd::disableUnitFiles(Systemd::System, QStringList() << ALARM_TIMER, true);
        }
    }
}

void AlarmConfig::bStartTestAlarm_onClicked()
{
    testAlarmProcess.setProcessChannelMode(QProcess::SeparateChannels);
    testAlarmProcess.start("bash", QStringList() << "-c" << ALARM_SCRIPT);
}

void AlarmConfig::bStopTestAlarm_onClicked()
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("mpc", QStringList() << "stop");
    while(builder.waitForFinished())
        ;
    testAlarmProcess.kill();
}

void AlarmConfig::bSaveAlarm_onClicked(const int minVolume, const int maxVolume, const int defaultVolume, const int growingVolume, const int growingSpeed, const bool isNewestSongsList,
                                       const QString playlist)
{
    QString minVolumeString = QString::number(minVolume);
    QString maxVolumeString = QString::number(maxVolume);
    QString defaultVolumeString = QString::number(defaultVolume);
    QString growingVolumeString = QString::number(growingVolume);
    QString growingSpeedString = QString::number(growingSpeed);
    QString isNewestSongsListString = isNewestSongsList ? "true" : "false";
    mAlarmConfigs.at("minVolume") = minVolumeString;
    mAlarmConfigs.at("maxVolume") = maxVolumeString;
    mAlarmConfigs.at("defaultVolume") = defaultVolumeString;
    mAlarmConfigs.at("growingVolume") = growingVolumeString;
    mAlarmConfigs.at("growingSpeed") = growingSpeedString;
    mAlarmConfigs.at("playlist") = playlist;
    mAlarmConfigs.at("theNewestSongs") = isNewestSongsListString;
    editAlarmConfigFile.SaveConfiguration(mAlarmConfigs);
}

void AlarmConfig::bSaveAlarmService_onClicked(const bool monCheckBox, const bool tueCheckBox, const bool wedCheckBox, const bool thuCheckBox, const bool friCheckBox, const bool satCheckBox,
                                              const bool sunCheckBox, const int timeHHSpinBox, const int timeMMSpinBox)
{
    QString daysOfWeek;

    if(monCheckBox)
        daysOfWeek += "Mon,";
    if(tueCheckBox)
        daysOfWeek += "Tue,";
    if(wedCheckBox)
        daysOfWeek += "Wed,";
    if(thuCheckBox)
        daysOfWeek += "Thu,";
    if(friCheckBox)
        daysOfWeek += "Fri,";
    if(satCheckBox)
        daysOfWeek += "Sat,";
    if(sunCheckBox)
        daysOfWeek += "Sun,";

    QString time;

    if(timeHHSpinBox < 10)
        time += "0";
    time += QString::number(timeHHSpinBox);
    time += ":";
    if(timeMMSpinBox < 10)
        time += "0";
    time += QString::number(timeMMSpinBox);

    daysOfWeek.remove(daysOfWeek.length() - 1, 1);// remove ',' on last sign

    saveAlarmIsSystemdTimer(daysOfWeek, time);
    if(systemdAlarmSupport)
        Systemd::reload(Systemd::System);
}


void AlarmConfig::saveAlarmIsSystemdTimer(const QString &daysOfWeek, const QString &time)
{
    QFile file(CONFIG_PATH + "/" + ALARM_TIMER);

    QStringList strings;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString qstrLine(line);

        if(qstrLine.contains("OnCalendar"))
        {
            strings.push_back("OnCalendar=" + daysOfWeek + " " + time + "\n");
        }
        else
        {
            strings.push_back(line);
        }
    }

    file.close();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(auto it = std::begin(strings); it != std::end(strings); ++it)
    {
        out << *it;
    }
    file.close();
}
