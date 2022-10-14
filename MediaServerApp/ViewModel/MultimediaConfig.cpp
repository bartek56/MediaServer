#include "MultimediaConfig.h"
#include "ConfigFile/ConfigFile.h"
#include <QtSystemd/sdmanager.h>

MultimediaConfig::MultimediaConfig(QObject *parent) : QObject(parent)
  ,dlnaConfigFile(std::make_shared<ConfigFile>(MINIDLNA_CONFIG_FILE))
  ,mpdConfigFile(std::make_shared<ConfigFile>(MPD_CONFIG_FILE))
{
    Systemd::getUnit(Systemd::System, DLNA_SERVICE);//support QDBusAbstractInterfaceSupport

    auto state = Systemd::getUnitFileState(Systemd::System, DLNA_SERVICE);

    if(state.contains("able"))
        systemdDlnaSupport = true;
    else
        qWarning() << "DLNA systemd not support";
    state = Systemd::getUnitFileState(Systemd::System, MPD_SERVICE);

    if(state.contains("able"))
        systemdMpdSupport = true;
    else
        qWarning() << "MPD systemd not support";
}

void MultimediaConfig::bVideoFileDialog_onAccepted(QString folderPath, QObject *tfVideoPath)
{
    QString path = folderPath.remove(0, 7);
    tfVideoPath->setProperty("text", QVariant(path));
    dlnaConfigs.setValueByKey(VIDEODIR,path);
}

void MultimediaConfig::bAudioFileDialog_onAccepted(QString folderPath, QObject *tfAudioPath)
{
    QString path = folderPath.remove(0, 7);
    tfAudioPath->setProperty("text", QVariant(path));
    dlnaConfigs.setValueByKey(AUDIODIR, path);
    mpdConfigs.setValueByKey(MUSIC_DIRECTORY, path);
    mpdConfigs.setValueByKey(PLAYLIST_DIRECTORY, path);
}

void MultimediaConfig::bPicturesFileDialog_onAccepted(QString folderPath, QObject *tfPicturesPath)
{
    QString path = folderPath.remove(0, 7);
    tfPicturesPath->setProperty("text", QVariant(path));
    dlnaConfigs.setValueByKey(PICTURESDIR, path);
}

void MultimediaConfig::tfName_onEditingFinished(const QString name)
{
    dlnaConfigs.setValueByKey(NAME, name);
}

void MultimediaConfig::tfPort_onEditingFinished(const QString port)
{
    dlnaConfigs.setValueByKey(PORT, port);
}

void MultimediaConfig::openConfigFile()
{
    if(!dlnaConfigFile.LoadConfiguration(dlnaConfigs))
    {
        qFatal("failed to load DLNA server configs");
    }
    if(!mpdConfigFile.LoadConfiguration(mpdConfigs))
    {
        qFatal("failed to load MPD server configs");
    }
}

void MultimediaConfig::loadMediaDirectoryConfigs(QObject *videoPath, QObject *audioPath, QObject *picturePath)
{
    videoPath->setProperty("text", QVariant(dlnaConfigs.getValueByKey(VIDEODIR)));
    audioPath->setProperty("text", QVariant(dlnaConfigs.getValueByKey(AUDIODIR)));
    picturePath->setProperty("text", QVariant(dlnaConfigs.getValueByKey(PICTURESDIR)));
}

void MultimediaConfig::loadSettings(QObject *port, QObject *name)
{
    port->setProperty("text", QVariant(dlnaConfigs.getValueByKey(PORT)));
    name->setProperty("text", QVariant(dlnaConfigs.getValueByKey(NAME)));
}

void MultimediaConfig::saveConfigs()
{
    if(!dlnaConfigFile.SaveConfiguration(dlnaConfigs))
        qFatal("Failed to save DLNA configuration");

    if(systemdDlnaSupport)
        restartService(DLNA_SERVICE);

    if(mpdConfigFile.SaveConfiguration(mpdConfigs))
         qFatal("Failed to save MPD configuration");

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
