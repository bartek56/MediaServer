#include "dlnaconfig.h"

DlnaConfig::DlnaConfig(QObject *parent) : QObject(parent)
{

}

void DlnaConfig::bVideoFileDialog_onAccepted(QString folderPath, QObject *tfVideoPath)
{
    QString path = folderPath.remove(0,7);
    tfVideoPath->setProperty("text",QVariant(path));
    mConfigs.at(VIDEODIR)=path;
}

void DlnaConfig::bAudioFileDialog_onAccepted(QString folderPath, QObject *tfAudioPath)
{
    QString path = folderPath.remove(0,7);
    tfAudioPath->setProperty("text",QVariant(path));
    mConfigs.at(AUDIODIR)=path;
}

void DlnaConfig::bPicturesFileDialog_onAccepted(QString folderPath, QObject *tfPicturesPath)
{
    QString path = folderPath.remove(0,7);
    tfPicturesPath->setProperty("text",QVariant(path));
    mConfigs.at(PICTURESDIR)=path;
}
void DlnaConfig::tfName_onEditingFinished(const QString name)
{
    mConfigs.at(NAME)=name;
}

void DlnaConfig::tfPort_onEditingFinished(const QString port)
{
    mConfigs.at(PORT)=port;
}

void DlnaConfig::openConfigFile()
{
    mConfigs = editDlnaConfigFile.OpenFile("/etc/minidlna.conf");
}

void DlnaConfig::loadMediaDirectoryConfigs(QObject *videoPath,QObject *audioPath,QObject *picturePath)
{
    videoPath->setProperty("text",QVariant(mConfigs.at(VIDEODIR)));
    audioPath->setProperty("text",QVariant(mConfigs.at(AUDIODIR)));
    picturePath->setProperty("text",QVariant(mConfigs.at(PICTURESDIR)));
}

void DlnaConfig::loadSettigs(QObject *port, QObject *name)
{
    port->setProperty("text",QVariant(mConfigs.at(PORT)));
    name->setProperty("text",QVariant(mConfigs.at(NAME)));
}

void DlnaConfig::saveConfigs()
{
    editDlnaConfigFile.SaveFile(mConfigs);
    QProcess::execute("systemctl restart minidlnad");
}
