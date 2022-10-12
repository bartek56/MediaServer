#ifndef DLNACONFIG_H
#define DLNACONFIG_H
#include <QtQuick>
#include "ConfigFile/DlnaConfigFile.h"
#include "ConfigFile/MpdConfigFile.h"

class MultimediaConfig : public QObject
{
    Q_OBJECT

public:
    explicit MultimediaConfig(QObject *parent = nullptr);
    Q_INVOKABLE void openConfigFile();
    Q_INVOKABLE void saveConfigs();
    Q_INVOKABLE void loadMediaDirectoryConfigs(QObject *videoPath, QObject *audioPath, QObject *picturePath);
    Q_INVOKABLE void loadSettings(QObject *port, QObject *name);
    Q_INVOKABLE void bVideoFileDialog_onAccepted(QString folderPath, QObject *textField);
    Q_INVOKABLE void tfPort_onEditingFinished(const QString port);
    Q_INVOKABLE void tfName_onEditingFinished(const QString name);
    Q_INVOKABLE void bAudioFileDialog_onAccepted(QString folderPath, QObject *tfAudioPath);
    Q_INVOKABLE void bPicturesFileDialog_onAccepted(QString folderPath, QObject *tfPicturesPath);

private:
    bool isServiceActive(QString serviceName);

    //dlna
    const QString PORT = "port";
    const QString AUDIODIR = "media_dir=A";
    const QString VIDEODIR = "media_dir=V";
    const QString PICTURESDIR = "media_dir=P";
    const QString NAME = "friendly_name";
    const QString DLNA_SERVICE = "minidlnad.service";
    bool systemdDlnaSupport = false;

    //mpd
    const QString MUSIC_DIRECTORY = "music_directory";
    const QString PLAYLIST_DIRECTORY = "playlist_directory";
    const QString MPD_SERVICE = "mpd.service";
    bool systemdMpdSupport = false;

    DlnaConfigFile editDlnaConfigFile;
    std::map<QString, QString> mDlnaConfigs;

    MpdConfigFile editMpdConfigFile;
    VectorData mMpdConfigs;
    void restartService(const QString &service);
};

#endif// DLNACONFIG_H
