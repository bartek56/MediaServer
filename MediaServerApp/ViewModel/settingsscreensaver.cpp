#include "settings.h"
#include "mainwindow.h"
#include "screensavermanager.h"

void Settings::screenSaverEnableSwitch_OnClicked(const bool isEnable)
{
    if(isEnable)
    {
        ScreenSaverManager::timer->start();
        mScreenSaverConfigs.at("enable")="true";
    }
    else
    {
        ScreenSaverManager::timer->stop();
        mScreenSaverConfigs.at("enable")="false";
    }
}


void Settings::bScreenSaverFileDialog_onAccepted(QString folderPath, QObject *tfScreenSavrFolderPath)
{
    QString path = folderPath.remove(0,7);
    tfScreenSavrFolderPath->setProperty("text",QVariant(path));
}

void Settings::bSaveScreenSaver_onClicked(const QString timeout, const QString path, const int startTime, const bool random)
{
    auto startTimeInMilisecond=startTime*60000;
    QString startTimeInMilisecondsString = QString::number(startTimeInMilisecond);
    mScreenSaverConfigs.at("startTime")=startTimeInMilisecondsString;
    mScreenSaverConfigs.at("timeout")=timeout;
    mScreenSaverConfigs.at("path")=path;
    if(random==true)
        mScreenSaverConfigs.at("random")="true";
    else
        mScreenSaverConfigs.at("random")="false";
    editScreenSaverConfigFile.SaveConfiguration(mScreenSaverConfigs);
    ScreenSaverManager::timer->setInterval(startTimeInMilisecond);
}


void Settings::loadScreenSaverConfigurations(QObject * enableSwitch, QObject *startTime, QObject *path, QObject *timeout, QObject *random)
{
    mScreenSaverConfigs = editScreenSaverConfigFile.LoadConfiguration();

    auto startTimeInMinutes = ConvertTimeFromMiliSecStringToMinutesInt(mScreenSaverConfigs.at("startTime"));

    startTime->setProperty("value",QVariant(startTimeInMinutes));
    path->setProperty("text",QVariant(mScreenSaverConfigs.at("path")));
    timeout->setProperty("value",QVariant(mScreenSaverConfigs.at("timeout")));
    if(mScreenSaverConfigs.at("random")=="true")
        random->setProperty("checked",QVariant(true));
    else
        random->setProperty("checked",QVariant(false));

    if(ScreenSaverManager::timer->isActive())
        enableSwitch->setProperty("checked", QVariant(true));
    else
        enableSwitch->setProperty("checked", QVariant(false));
}

int Settings::ConvertTimeFromMiliSecStringToMinutesInt(QString miliSecounds)
{
    int startTimeInMiliSeconds = miliSecounds.toInt();
    return startTimeInMiliSeconds/60000;
}

