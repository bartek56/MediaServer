#include "ScreenSaver.h"
#include "../ScreenSaverManager.h"

ScreenSaver::ScreenSaver(QObject *parent) : QObject(parent)
{

}


void ScreenSaver::init(QObject *timer, QObject *folderModel, QObject *screenSaverDialog)
{
    ScreenSaverManager::timer->stop();

    mConfigsParameters = editScreenSaverConfigFile.LoadConfiguration();

    QString path="file:" + mConfigsParameters.at("path");
    folderModel->setProperty("folder", QVariant(path));

    if(mConfigsParameters.at("random")=="true")
        screenSaverDialog->setProperty("isRandom", QVariant(true));
    else
        screenSaverDialog->setProperty("isRandom", QVariant(false));

    int interval = mConfigsParameters.at("timeout").toInt();
    interval=interval*1000;

    timer->setProperty("interval",QVariant(interval));
    timer->setProperty("running",QVariant(true));
}

void ScreenSaver::exit()
{
    ScreenSaverManager::timer->start();
}
