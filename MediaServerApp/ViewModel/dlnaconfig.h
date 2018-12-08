#ifndef DLNACONFIG_H
#define DLNACONFIG_H
#include <QtQuick>
#include "editdlnaconfigfile.h"

class DlnaConfig : public QObject
{
    Q_OBJECT

public:
    explicit DlnaConfig(QObject *parent = nullptr);
    Q_INVOKABLE void openConfigFile();
    Q_INVOKABLE void saveConfigs();
    Q_INVOKABLE void loadMediaDirectoryConfigs(QObject *videoPath,QObject *audioPath,QObject *picturePath);
    Q_INVOKABLE void loadSettigs(QObject *port, QObject *name);
    Q_INVOKABLE void bVideoFileDialog_onAccepted(QString folderPath, QObject *textField);
    Q_INVOKABLE void tfPort_onEditingFinished(const QString port);
    Q_INVOKABLE void tfName_onEditingFinished(const QString name);
    Q_INVOKABLE void bAudioFileDialog_onAccepted(QString folderPath, QObject *tfAudioPath);
    Q_INVOKABLE void bPicturesFileDialog_onAccepted(QString folderPath, QObject *tfPicturesPath);
    Q_INVOKABLE void checkService(QObject *saveButton);

private:
    const QString PORT = "port";
    const QString AUDIODIR = "media_dir=A";
    const QString VIDEODIR = "media_dir=V";
    const QString PICTURESDIR = "media_dir=P";
    const QString NAME = "friendly_name";
    EditDlnaConfigFile editDlnaConfigFile;
    std::map<QString, QString> mConfigs;

};

#endif // DLNACONFIG_H
