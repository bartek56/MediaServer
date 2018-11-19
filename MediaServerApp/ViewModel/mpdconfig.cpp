#include "mpdconfig.h"


MpdConfig::MpdConfig(QObject *parent) : QObject(parent)
{

}

void MpdConfig::bMusicFileDialog_onAccepted(QString folderPath, QObject *tfMusicPath)
{
    QString path = folderPath.remove(0,7);
    tfMusicPath->setProperty("text",QVariant(path));
    mConfigs.at(MUSIC_DIRECTORY)=path;
}

void MpdConfig::loadConfigs(QObject *tfMusicPath)
{
    mConfigs = editMpdConfigFile.OpenFile("/etc/mpd.conf");
    tfMusicPath->setProperty("text",QVariant(mConfigs.at(MUSIC_DIRECTORY)));
}

void MpdConfig::saveConfigs()
{
    editMpdConfigFile.SaveFile(mConfigs);
    QProcess::execute("systemctl restart mpd.service");
}