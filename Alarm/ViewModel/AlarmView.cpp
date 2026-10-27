#include "AlarmView.h"
#include "ConfigFile/ConfigFile.h"
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include "SystemdManager.h"

AlarmView::AlarmView(QObject *parent) : QObject(parent)
  ,editAlarmConfigFile(ALARM_CONFIG_FILE)
{
    if(SystemdManager::unitFileExists(ALARM_SNOOZE_SERVICE))
    {
        const bool alarmSnoozeActive = SystemdManager::isUnitActive(ALARM_SNOOZE_SERVICE);
        const bool alarmActive = SystemdManager::isUnitActive(ALARM_SERVICE);

        if(alarmSnoozeActive)
        {
            isSnooze = true;
        }
        if(alarmSnoozeActive || alarmActive)
        {
            systemdSupportExist = true;
        }
    }
    else
    {
        qWarning() << "alarm service not exist";
    }

    loadAlarmTime();
}

void AlarmView::loadAlarmTime()
{
    const QString timer = isSnooze ? ALARM_SNOOZE_TIMER : ALARM_TIMER;
    QFile file(QString(CONFIG_PATH) + "/" + timer);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file.atEnd())
    {
        const QString line = QString::fromUtf8(file.readLine()).trimmed();
        if(!line.startsWith("OnCalendar="))
            continue;

        const QStringList parts = line.mid(QStringLiteral("OnCalendar=").size()).split(' ');
        if(parts.size() > 1)
        {
            const QString time = parts.at(1);
            if(time.size() >= 5)
                m_alarmTime = time.left(5);
        }
        break;
    }
}

void AlarmView::refreshCurrentSong()
{
    QProcess mpc;
    mpc.start("mpc", QStringList() << "-f" << "%title% — %artist%" << "current");

    if(!mpc.waitForFinished(1000))
        return;

    QString song = QString::fromUtf8(mpc.readAllStandardOutput()).trimmed();
    if(song.isEmpty())
        song = tr("Odtwarzanie alarmu");

    setCurrentSong(song);
}

void AlarmView::setCurrentSong(const QString &song)
{
    if(m_currentSong == song)
        return;

    m_currentSong = song;
    emit currentSongChanged();
}

void AlarmView::stopAlarm()
{
    if(systemdSupportExist)
    {
        SystemdManager::stopUnit(ALARM_SNOOZE_TIMER);

        if(isSnooze)
            SystemdManager::stopUnit(ALARM_SNOOZE_SERVICE);

        else
            SystemdManager::stopUnit(ALARM_SERVICE);

        VectorData alarmConfigMap;
        editAlarmConfigFile.LoadConfiguration(alarmConfigMap);
        QString defaultVolume = alarmConfigMap.getValueByKey("default_volume");
        QProcess::startDetached("mpc", QStringList() << "volume" << defaultVolume);
    }
}

void AlarmView::snooze5min()
{
    if(systemdSupportExist)
        snooze(5);
}

void AlarmView::snooze10min()
{
    if(systemdSupportExist)
        snooze(10);
}

void AlarmView::snooze15min()
{
    if(systemdSupportExist)
        snooze(15);
}

void AlarmView::snooze(int min)
{
    QFile file(QString(CONFIG_PATH) + "/" + ALARM_SNOOZE_TIMER);

    QStringList vUsers;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString qstrLine(line);

        if(qstrLine.contains("OnCalendar"))
        {
            QDateTime local(QDateTime::currentDateTime());
            local = local.addSecs(60 * min);
            vUsers.push_back("OnCalendar=*-*-* " + local.toString("hh:mm") + "\n");
        }
        else
        {
            vUsers.push_back(line);
        }
    }

    file.close();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(auto it = std::begin(vUsers); it != std::end(vUsers); ++it)
    {
        out << *it;
    }
    file.close();

    SystemdManager::reload();

    QProcess::startDetached("mpc", QStringList() << "stop");
    SystemdManager::restartUnit(ALARM_SNOOZE_TIMER);

    if(isSnooze)
        SystemdManager::stopUnit(ALARM_SNOOZE_SERVICE);
    else
        SystemdManager::stopUnit(ALARM_SERVICE);
}
