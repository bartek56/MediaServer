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
    timer->start();
}

void ScreenSaverManager::startScreen()
{
    QProcess::startDetached("systemctl start screensaver.service");
    QProcess::startDetached("systemctl stop start.service");
}

void ScreenSaverManager::resetTimer()
{
    timer->start();
}
