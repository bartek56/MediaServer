#include "settings.h"
#include "mainwindow.h"
#include "screensaver.h"

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
        mScreenSaverConfigs.at("random")="-z";
    else
        mScreenSaverConfigs.at("random")="";
    editScreenSaverConfigFile.SaveConfiguration(SCREENSAVER_SCRIPT, mScreenSaverConfigs);
    ScreenSaver::timer->setInterval(startTimeInMilisecond);
}


void Settings::loadScreenSaverConfigurations(QObject *startTime, QObject *path, QObject *timeout, QObject *random)
{
    mScreenSaverConfigs = editScreenSaverConfigFile.LoadConfiguration(SCREENSAVER_SCRIPT);

    auto startTimeInMinutes = ConvertTimeFromMiliSecStringToMinutesInt(mScreenSaverConfigs.at("startTime"));

    startTime->setProperty("value",QVariant(startTimeInMinutes));
    path->setProperty("text",QVariant(mScreenSaverConfigs.at("path")));
    timeout->setProperty("value",QVariant(mScreenSaverConfigs.at("timeout")));
    if(mScreenSaverConfigs.at("random").size()>1)
        random->setProperty("checked",QVariant(true));
    else
        random->setProperty("checked",QVariant(false));
}

int Settings::ConvertTimeFromMiliSecStringToMinutesInt(QString miliSecounds)
{
    int startTimeInMiliSeconds = miliSecounds.toInt();
    return startTimeInMiliSeconds/60000;
}

