#include "screensavermanager.h"
#include "ViewModel/mainwindow.h"
#include <QProcess>

ScreenSaverManager::ScreenSaverManager(QObject *parent) : QObject(parent)
{
 qDebug() << "screen saver constructor";
}

void ScreenSaverManager::Init()
{
//    auto mConfigs = editScreenSaverConfigFile.LoadConfiguration("/opt/startScreensaver.sh");
    timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), this, SLOT(startScreen()));
//    QString startTimeString = mConfigs.at("startTime");
//    int startTimeInt = startTimeString.toInt();
//    timer->setInterval(startTimeInt);
//    timer->start();

 qDebug() << "screen saver init";

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
