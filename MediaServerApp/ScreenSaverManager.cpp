#include "ScreenSaverManager.h"
#include "ViewModel/MainWindow.h"
#include "ConfigFile/ConfigFile.h"
#include <QProcess>

ScreenSaverManager::ScreenSaverManager(QObject *parent) : QObject(parent)
  ,screenSaverConfigFile(std::make_shared<ConfigFile>(SCREENSAVER_CONFIG_FILE))
{
}

void ScreenSaverManager::Init()
{
    VectorData configs;
    bool result = screenSaverConfigFile.LoadConfiguration(configs);
    if(result)
    {
        if(configs.getValueByKey("enable") == "true")
        {
            timer = new QTimer();
            QString startTimeString = configs.getValueByKey("startTime");
            timer->setInterval(startTimeString.toInt());
            timer->start();
        }
    }
    else
    {
        qCritical("Failed to load ScreenSaver configuration");
    }
}

void ScreenSaverManager::resetTimer()
{
    if(timer->isActive())
        timer->start();
}
