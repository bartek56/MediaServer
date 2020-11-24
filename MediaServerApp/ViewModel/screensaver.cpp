#include "screensaver.h"
#include "screensavermanager.h"

ScreenSaver::ScreenSaver(QObject *parent) : QObject(parent)
{

}


void ScreenSaver::init(QObject *timer, QObject *folderModel)
{
    ScreenSaverManager::timer->stop();

    mConfigsParameters = editScreenSaverConfigFile.LoadConfiguration();

    /// TODO
    //random

    QString path="file:" + mConfigsParameters.at("path");
    folderModel->setProperty("folder", QVariant(path));

    int interval = mConfigsParameters.at("timeout").toInt();
    interval=interval*1000;

    timer->setProperty("interval",QVariant(interval));
    timer->setProperty("running",QVariant(true));
}

void ScreenSaver::exit()
{
    ScreenSaverManager::timer->start();
}
