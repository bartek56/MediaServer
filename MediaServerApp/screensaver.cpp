#include "screensaver.h"
#include "ViewModel/mainwindow.h"
#include <QProcess>

ScreenSaver::ScreenSaver(QObject *parent) : QObject(parent)
{

}

void ScreenSaver::Init()
{
    auto mConfigs = editScreenSaverConfigFile.LoadConfiguration("/opt/startScreensaver.sh");
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(startScreen()));
    QString startTimeString = mConfigs.at("startTime");
    int startTimeInt = startTimeString.toInt();
    timer->setInterval(startTimeInt);
    timer->start();
}

void ScreenSaver::startScreen()
{
    QProcess::startDetached("systemctl start screensaver.service");
    QProcess::startDetached("systemctl stop start.service");
}

void ScreenSaver::resetTimer()
{
    timer->start();
}
