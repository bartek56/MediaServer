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
    QString commend="xinit -- -nocursor";
    qint64 pid;
    QProcess appProcess;
    appProcess.startDetached("sh", QStringList() << "-c" << commend,QProcess::nullDevice(),&pid);
    QString strPid = QString::number(pid);
    QString commend2 = "/opt/startScreensaver.sh "+strPid;
    qint64 pid2;
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << commend2,QProcess::nullDevice(),&pid2);
    MainWindow::mainView->destroy();
}

void ScreenSaver::resetTimer()
{
    timer->start();
}
