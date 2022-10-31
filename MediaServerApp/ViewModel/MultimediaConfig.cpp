#include "MultimediaConfig.h"
#include "ConfigFile/ConfigFile.h"
#include <QtSystemd/sdmanager.h>

MultimediaConfig::MultimediaConfig(QObject *parent) : QObject(parent), dlnaConfigFile(std::make_shared<ConfigFile>(MINIDLNA_CONFIG_FILE)), mpdConfigFile(std::make_shared<ConfigFile>(MPD_CONFIG_FILE))
{
    Systemd::getUnit(Systemd::System, DLNA_SERVICE);//support QDBusAbstractInterfaceSupport

    auto state = Systemd::getUnitFileState(Systemd::System, DLNA_SERVICE);

    if(state.contains("able"))
    {
        systemdDlnaSupport = true;
    }
    else
    {
        systemdDlnaSupport = false;
        qWarning() << "DLNA systemd not support";
    }
    state = Systemd::getUnitFileState(Systemd::System, MPD_SERVICE);

    if(state.contains("able"))
    {
        systemdMpdSupport = true;
    }
    else
    {
        systemdMpdSupport = false;
        qWarning() << "MPD systemd not support";
    }
}

bool MultimediaConfig::isFileValid() const
{
    if(QFile(MINIDLNA_CONFIG_FILE).exists() and QFile(MPD_CONFIG_FILE).exists())
    {
        return true;
    }

    return false;
}

void MultimediaConfig::bVideoFileDialog_onAccepted(QString folderPath, QObject *tfVideoPath)
{
    if(isDlnaSettingsLoaded)
    {
        QString path = folderPath.remove(0, 7);
        tfVideoPath->setProperty("text", QVariant(path));
        dlnaConfigs.setValueByKey(VIDEODIR, path);
    }
}

void MultimediaConfig::bAudioFileDialog_onAccepted(QString folderPath, QObject *tfAudioPath)
{
    if(isDlnaSettingsLoaded and isMpdSettingsLoaded)
    {
        QString path = folderPath.remove(0, 7);
        tfAudioPath->setProperty("text", QVariant(path));
        dlnaConfigs.setValueByKey(AUDIODIR, path);
        mpdConfigs.setValueByKey(MUSIC_DIRECTORY, path);
        mpdConfigs.setValueByKey(PLAYLIST_DIRECTORY, path);
    }
}

void MultimediaConfig::bPicturesFileDialog_onAccepted(QString folderPath, QObject *tfPicturesPath)
{
    if(isDlnaSettingsLoaded)
    {
        QString path = folderPath.remove(0, 7);
        tfPicturesPath->setProperty("text", QVariant(path));
        dlnaConfigs.setValueByKey(PICTURESDIR, path);
    }
}

void MultimediaConfig::tfName_onEditingFinished(const QString name)
{
    if(isDlnaSettingsLoaded)
        dlnaConfigs.setValueByKey(NAME, name);
}

void MultimediaConfig::tfPort_onEditingFinished(const QString port)
{
    if(isDlnaSettingsLoaded)
        dlnaConfigs.setValueByKey(PORT, port);
}

void MultimediaConfig::loadSettings(QObject *videoPath, QObject *audioPath, QObject *picturePath, QObject *port, QObject *name)
{
    if(dlnaConfigFile.LoadConfiguration(dlnaConfigs))
    {
        isDlnaSettingsLoaded = true;
        videoPath->setProperty("text", QVariant(dlnaConfigs.getValueByKey(VIDEODIR)));
        audioPath->setProperty("text", QVariant(dlnaConfigs.getValueByKey(AUDIODIR)));
        picturePath->setProperty("text", QVariant(dlnaConfigs.getValueByKey(PICTURESDIR)));
        port->setProperty("text", QVariant(dlnaConfigs.getValueByKey(PORT)));
        name->setProperty("text", QVariant(dlnaConfigs.getValueByKey(NAME)));
    }
    else
    {
        isDlnaSettingsLoaded = false;
        qCritical("Failed to load DLNA configuration");
    }


    if(mpdConfigFile.LoadConfiguration(mpdConfigs))
    {
        isMpdSettingsLoaded = true;
    }
    else
    {
        isMpdSettingsLoaded = false;
        qCritical("Failed to load MPD configuration");
    }
}

void MultimediaConfig::saveConfigs()
{
    if(!dlnaConfigFile.SaveConfiguration(dlnaConfigs))
        qCritical("Failed to save DLNA configuration");

    if(systemdDlnaSupport)
        restartService(DLNA_SERVICE);

    if(!mpdConfigFile.SaveConfiguration(mpdConfigs))
        qCritical("Failed to save MPD configuration");

    if(systemdMpdSupport)
        restartService(MPD_SERVICE);
}
void MultimediaConfig::restartService(const QString &service)
{
    if(isServiceActive(service))
        Systemd::restartUnit(Systemd::System, service, Systemd::Unit::Replace);
}

bool MultimediaConfig::isServiceActive(QString serviceName)
{
    auto text = Systemd::loadUnit(Systemd::System, serviceName)->activeState();
    return !text.contains("in");
}
