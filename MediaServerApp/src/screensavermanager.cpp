#include "screensavermanager.h"
#include "ViewModel/mainwindow.h"
#include <QProcess>

ScreenSaverManager::ScreenSaverManager(QObject *parent) : QObject(parent)
{
}

void ScreenSaverManager::Init()
{
    auto mConfigs = editScreenSaverConfigFile.LoadConfiguration();
    timer = new QTimer();
    QString startTimeString = mConfigs.at("startTime");
    timer->setInterval(startTimeString.toInt());
    if(mConfigs.at("enable") == "true")
        timer->start();
}

void ScreenSaverManager::startScreen()
{
    QProcess::startDetached("systemctl", QStringList() << "start"
                                                       << "screensaver.service");
    QProcess::startDetached("systemctl", QStringList() << "stop"
                                                       << "start.service");
}

void ScreenSaverManager::resetTimer()
{
    if(timer->isActive())
        timer->start();
}
