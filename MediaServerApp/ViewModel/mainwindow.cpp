#include "mainwindow.h"
#include <QProcess>
#include <QTimer>

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{

}

void MainWindow::startPicturesApplication()
{

    QString commend="xinit /usr/bin/gqview";
    //startApplication(commend);
}

void MainWindow::startMusicApplication()
{
    QString commend="xinit /usr/bin/gmpc";
    //startApplication(commend);
}

void MainWindow::startVideoApplication()
{

}

void MainWindow::startApplication(QString commend)
{
    qint64 pid;
    QProcess appProcess;
    appProcess.startDetached("sh", QStringList() << "-c" << commend,QProcess::nullDevice(),&pid);
    QString strPid = QString::number(pid);
    QString commend2 = "/opt/script.sh "+strPid;
    qint64 pid2;
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << commend2,QProcess::nullDevice(),&pid2);
    MainWindow::mainView->destroy();
}
