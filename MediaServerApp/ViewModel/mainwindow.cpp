#include "mainwindow.h"
#include "screensaver.h"
#include <QProcess>
#include <QTimer>

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{

}

void MainWindow::startPicturesApplication()
{
    QString commend="xinit /usr/bin/gqview -- -nocursor";
    startApplication(commend);
}

void MainWindow::startMusicApplication()
{
    QString commend="xinit /usr/bin/gmpc -- -nocursor";
    startApplication(commend);
}

void MainWindow::startVideoApplication()
{
    /*
    QString commend="xinit";
    qint64 pid;
    QProcess appProcess;
    appProcess.startDetached("sh", QStringList() << "-c" << commend,QProcess::nullDevice(),&pid);
    QString strPid = QString::number(pid);
    QString commend2 = "/opt/startGMPlayer.sh "+strPid;

    qint64 pid2;
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << commend2,QProcess::nullDevice(),&pid2);
    MainWindow::mainView->destroy();
    */
    QString commend2 = "/opt/startVideoPlayer.sh";
    qint64 pid2;
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << commend2,QProcess::nullDevice(),&pid2);
    MainWindow::mainView->destroy();

}

void MainWindow::startApplication(QString commend)
{
    qint64 pid;
    QProcess appProcess;
    appProcess.startDetached("sh", QStringList() << "-c" << commend,QProcess::nullDevice(),&pid);
    QString strPid = QString::number(pid);
    QString commend2 = "/opt/start.sh "+strPid;
    qint64 pid2;
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << commend2,QProcess::nullDevice(),&pid2);
    MainWindow::mainView->destroy();
}

void MainWindow::startWebBrowser()
{
    QString commend2 = "/opt/startWebBrowser.sh";
    qint64 pid2;
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << commend2,QProcess::nullDevice(),&pid2);
    MainWindow::mainView->destroy();
}

void MainWindow::startBrowser()
{
    QString commend="xinit /usr/bin/pcmanfm -- -nocursor";
    startApplication(commend);
}
