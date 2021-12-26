#include "multimediaconfig.h"

MultimediaConfig::MultimediaConfig(QObject *parent) : QObject(parent)
{

}

void MultimediaConfig::bVideoFileDialog_onAccepted(QString folderPath, QObject *tfVideoPath)
{
    QString path = folderPath.remove(0,7);
    tfVideoPath->setProperty("text",QVariant(path));
    mDlnaConfigs.at(VIDEODIR)=path;
}

void MultimediaConfig::bAudioFileDialog_onAccepted(QString folderPath, QObject *tfAudioPath)
{
    QString path = folderPath.remove(0,7);
    tfAudioPath->setProperty("text",QVariant(path));
    mDlnaConfigs.at(AUDIODIR)=path;
    mMpdConfigs.at(MUSIC_DIRECTORY)=path;
    mMpdConfigs.at(PLAYLIST_DIRECTORY)=path;
}

void MultimediaConfig::bPicturesFileDialog_onAccepted(QString folderPath, QObject *tfPicturesPath)
{
    QString path = folderPath.remove(0,7);
    tfPicturesPath->setProperty("text",QVariant(path));
    mDlnaConfigs.at(PICTURESDIR)=path;
}

void MultimediaConfig::tfName_onEditingFinished(const QString name)
{
    mDlnaConfigs.at(NAME)=name;
}

void MultimediaConfig::tfPort_onEditingFinished(const QString port)
{
    mDlnaConfigs.at(PORT)=port;
}

void MultimediaConfig::openConfigFile()
{
    mDlnaConfigs = editDlnaConfigFile.OpenFile();
    mMpdConfigs = editMpdConfigFile.OpenFile();
}

void MultimediaConfig::loadMediaDirectoryConfigs(QObject *videoPath,QObject *audioPath,QObject *picturePath)
{
    videoPath->setProperty("text",QVariant(mDlnaConfigs.at(VIDEODIR)));
    audioPath->setProperty("text",QVariant(mDlnaConfigs.at(AUDIODIR)));
    picturePath->setProperty("text",QVariant(mDlnaConfigs.at(PICTURESDIR)));
}

void MultimediaConfig::loadSettings(QObject *port, QObject *name)
{
    port->setProperty("text",QVariant(mDlnaConfigs.at(PORT)));
    name->setProperty("text",QVariant(mDlnaConfigs.at(NAME)));
}

void MultimediaConfig::saveConfigs()
{
    editDlnaConfigFile.SaveFile(mDlnaConfigs);
    editMpdConfigFile.SaveFile(mMpdConfigs);
    if(isServiceActive(DLNA_SERVICE))
        QProcess::execute("systemctl restart "+DLNA_SERVICE);

    if(isServiceActive(MPD_SERVICE))
        QProcess::execute("systemctl restart "+MPD_SERVICE);
}

bool MultimediaConfig::isServiceActive(QString serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QString commend = "systemctl is-active " + serviceName;
    process.start("bash", QStringList() << "-c" << commend);
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    return !text.contains("in");
}
