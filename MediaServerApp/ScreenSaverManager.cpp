#include "ScreenSaverManager.h"
#include "ViewModel/MainWindow.h"
#include "ConfigFile/ConfigFile.h"
#include <QProcess>

ScreenSaverManager::ScreenSaverManager(QObject *parent) : QObject(parent), screenSaverConfigFile(std::make_unique<ConfigFile>(SCREENSAVER_CONFIG_FILE))
{
    timer = new QTimer();
}

bool ScreenSaverManager::Init()
{
    VectorData configs;
    bool result = screenSaverConfigFile.LoadConfiguration(configs);
    if(!result)
    {
        qCritical("Failed to load screen saver configuration");
        return false;
    }

    if(configs.getValueByKey("enable") == "true")
    {
        QString startTimeString = configs.getValueByKey("startTime");
        timer->setInterval(startTimeString.toInt());
        timer->start();
    }
    return true;
}

void ScreenSaverManager::resetTimer()
{
    if(timer->isActive())
        timer->start();
}
