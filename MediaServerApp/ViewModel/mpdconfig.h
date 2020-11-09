#ifndef MPDCONFIG_H
#define MPDCONFIG_H

#include <QtQuick>
#include <QObject>
#include "editmpdconfigfile.h"

class MpdConfig : public QObject
{
    Q_OBJECT
public:
    explicit MpdConfig(QObject *parent = nullptr);
    Q_INVOKABLE void bMusicFileDialog_onAccepted(QString folderPath, QObject *tfMusicPath);
    Q_INVOKABLE void loadConfigs(QObject *tfMusicPath);
    Q_INVOKABLE void saveConfigs(const QString path);
    Q_INVOKABLE void checkService(QObject *bSave);

signals:

public slots:

private:
    const QString MUSIC_DIRECTORY="music_directory";
    EditMpdConfigFile editMpdConfigFile;
    std::map<QString, QString> mConfigs;
};

#endif // MPDCONFIG_H
