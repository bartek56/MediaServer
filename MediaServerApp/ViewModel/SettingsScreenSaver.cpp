#include "SettingsScreenSaver.h"
#include "MainWindow.h"
#include "ConfigFile/ConfigFile.h"
#include "../ScreenSaverManager.h"

SettingsScreensaver::SettingsScreensaver(QObject *parent) : QObject(parent), screenSaverConfigFile(std::make_shared<ConfigFile>(SCREENSAVER_CONFIG_FILE))
{
}

void SettingsScreensaver::screenSaverEnableSwitch_OnClicked(const bool isEnable)
{
    if(isEnable)
    {
        ScreenSaverManager::timer->start();
        screenSaverConfigs.setValueByKey("enable", "true");
    }
    else
    {
        ScreenSaverManager::timer->stop();
        screenSaverConfigs.setValueByKey("enable", "false");
    }
}

void SettingsScreensaver::bScreenSaverFileDialog_onAccepted(QString folderPath, QObject *tfScreenSavrFolderPath)
{
    QString path = folderPath.remove(0, 7);
    tfScreenSavrFolderPath->setProperty("text", QVariant(path));
}

void SettingsScreensaver::bSaveScreenSaver_onClicked(const QString timeout, const QString path, const int startTime, const bool random)
{
    auto startTimeInMilisecond = startTime * 60000;
    QString startTimeInMilisecondsString = QString::number(startTimeInMilisecond);
    screenSaverConfigs.setValueByKey("startTime", startTimeInMilisecondsString);
    screenSaverConfigs.setValueByKey("timeout", timeout);
    screenSaverConfigs.setValueByKey("path", path);
    if(random == true)
        screenSaverConfigs.setValueByKey("random", "true");
    else
        screenSaverConfigs.setValueByKey("random", "false");
    const bool result = screenSaverConfigFile.SaveConfiguration(screenSaverConfigs);
    if(!result)
        qCritical("Failed to save ScreenSaver configuration");
    ScreenSaverManager::timer->setInterval(startTimeInMilisecond);
}

void SettingsScreensaver::loadScreenSaverConfigurations(QObject *enableSwitch, QObject *startTime, QObject *path, QObject *timeout, QObject *random)
{
    const bool result = screenSaverConfigFile.LoadConfiguration(screenSaverConfigs);
    if(result)
    {
        auto startTimeInMinutes = ConvertTimeFromMiliSecStringToMinutesInt(screenSaverConfigs.getValueByKey("startTime"));

        startTime->setProperty("value", QVariant(startTimeInMinutes));
        path->setProperty("text", QVariant(screenSaverConfigs.getValueByKey("path")));
        timeout->setProperty("value", QVariant(screenSaverConfigs.getValueByKey("timeout")));
        if(screenSaverConfigs.getValueByKey("random") == "true")
            random->setProperty("checked", QVariant(true));
        else
            random->setProperty("checked", QVariant(false));

        if(ScreenSaverManager::timer->isActive())
            enableSwitch->setProperty("checked", QVariant(true));
        else
            enableSwitch->setProperty("checked", QVariant(false));
    }
    else
    {
        qCritical("Error to load screensaver configuration");
    }
}

int SettingsScreensaver::ConvertTimeFromMiliSecStringToMinutesInt(QString miliSecounds)
{
    int startTimeInMiliSeconds = miliSecounds.toInt();
    return startTimeInMiliSeconds / 60000;
}
