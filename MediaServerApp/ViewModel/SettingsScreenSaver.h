#ifndef SETTINGSSCREENSAVER_H
#define SETTINGSSCREENSAVER_H

#include <QObject>
#include <ConfigFile/ScreenSaverConfigFile.h>

class SettingsScreensaver : public QObject
{
private:
    // Screensaver
    ScreenSaverConfigFile editScreenSaverConfigFile;
    std::map<QString, QString> mScreenSaverConfigs;
    int ConvertTimeFromMiliSecStringToMinutesInt(QString milisec);


    Q_OBJECT
public:
    explicit SettingsScreensaver(QObject *parent = nullptr);

    // ScreenSaver
    Q_INVOKABLE void bScreenSaverFileDialog_onAccepted(QString folderPath, QObject *tfScreenSavrFolderPath);
    Q_INVOKABLE void bSaveScreenSaver_onClicked(const QString timeout, const QString path, const int startTime, const bool random);
    Q_INVOKABLE void loadScreenSaverConfigurations(QObject *screensaverEnableSwitch, QObject *startTime, QObject *path,
                                                   QObject *timeout, QObject *random);
    Q_INVOKABLE void screenSaverEnableSwitch_OnClicked(const bool isEnable);
};

#endif // SETTINGSSCREENSAVER_H
