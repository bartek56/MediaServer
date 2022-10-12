#include "MultimediaConfig.h"
#include "ConfigFile/ConfigFile.h"
#include <QtSystemd/sdmanager.h>

MultimediaConfig::MultimediaConfig(QObject *parent) : QObject(parent),editMpdConfigFile(std::make_shared<ConfigFile>("/etc/mediaserver/minidlna.conf"))
{
    Systemd::getUnit(Systemd::System, DLNA_SERVICE);//support QDBusAbstractInterfaceSupport

    auto state = Systemd::getUnitFileState(Systemd::System, DLNA_SERVICE);

    if(state.contains("able"))
        systemdDlnaSupport = true;
    else
        qDebug() << "DLNA systemd not support";
    state = Systemd::getUnitFileState(Systemd::System, MPD_SERVICE);

    if(state.contains("able"))
        systemdMpdSupport = true;
    else
        qDebug() << "MPD systemd not support";
}

void MultimediaConfig::bVideoFileDialog_onAccepted(QString folderPath, QObject *tfVideoPath)
{
    QString path = folderPath.remove(0, 7);
    tfVideoPath->setProperty("text", QVariant(path));
    mDlnaConfigs.at(VIDEODIR) = path;
}

void MultimediaConfig::bAudioFileDialog_onAccepted(QString folderPath, QObject *tfAudioPath)
{
    QString path = folderPath.remove(0, 7);
    tfAudioPath->setProperty("text", QVariant(path));
    mDlnaConfigs.at(AUDIODIR) = path;
    mMpdConfigs.setValueByKey(MUSIC_DIRECTORY, path);
    mMpdConfigs.setValueByKey(PLAYLIST_DIRECTORY, path);
}

void MultimediaConfig::bPicturesFileDialog_onAccepted(QString folderPath, QObject *tfPicturesPath)
{
    QString path = folderPath.remove(0, 7);
    tfPicturesPath->setProperty("text", QVariant(path));
    mDlnaConfigs.at(PICTURESDIR) = path;
}

void MultimediaConfig::tfName_onEditingFinished(const QString name)
{
    mDlnaConfigs.at(NAME) = name;
}

void MultimediaConfig::tfPort_onEditingFinished(const QString port)
{
    mDlnaConfigs.at(PORT) = port;
}

void MultimediaConfig::openConfigFile()
{
    mDlnaConfigs = editDlnaConfigFile.OpenFile();
    editMpdConfigFile.OpenFile(mMpdConfigs);
}

void MultimediaConfig::loadMediaDirectoryConfigs(QObject *videoPath, QObject *audioPath, QObject *picturePath)
{
    videoPath->setProperty("text", QVariant(mDlnaConfigs.at(VIDEODIR)));
    audioPath->setProperty("text", QVariant(mDlnaConfigs.at(AUDIODIR)));
    picturePath->setProperty("text", QVariant(mDlnaConfigs.at(PICTURESDIR)));
}

void MultimediaConfig::loadSettings(QObject *port, QObject *name)
{
    port->setProperty("text", QVariant(mDlnaConfigs.at(PORT)));
    name->setProperty("text", QVariant(mDlnaConfigs.at(NAME)));
}

void MultimediaConfig::saveConfigs()
{
    editDlnaConfigFile.SaveFile(mDlnaConfigs);
    if(systemdDlnaSupport)
        restartService(DLNA_SERVICE);

    editMpdConfigFile.SaveFile(mMpdConfigs);
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
