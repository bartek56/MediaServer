#include "ScreenSaver.h"
#include "ViewModel/ScreenSaver/ScreenSaverManager.h"
#include "ConfigFile/ConfigFile.h"

ScreenSaver::ScreenSaver(QObject *parent) : QObject(parent), screenSaverConfigFile(std::make_unique<ConfigFile>(SCREENSAVER_CONFIG_FILE))
{
}


void ScreenSaver::init(QObject *timer, QObject *folderModel, QObject *screenSaverDialog)
{
    ScreenSaverManager::timer->stop();

    const bool result = screenSaverConfigFile.LoadConfiguration(screenSaverConfigs);

    if(result)
    {
        QString path = "file:" + screenSaverConfigs.getValueByKey("path");
        folderModel->setProperty("folder", QVariant(path));

        if(screenSaverConfigs.getValueByKey("random") == "true")
            screenSaverDialog->setProperty("isRandom", QVariant(true));
        else
            screenSaverDialog->setProperty("isRandom", QVariant(false));

        int interval = screenSaverConfigs.getValueByKey("timeout").toInt();
        interval = interval * 1000;

        timer->setProperty("interval", QVariant(interval));
        timer->setProperty("running", QVariant(true));
    }
    else
    {
        qCritical("Error to load ScreenSaver configuration");
    }
}

void ScreenSaver::exit()
{
    ScreenSaverManager::timer->start();
}
