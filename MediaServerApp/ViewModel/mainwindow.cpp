#include "mainwindow.h"
#include <QProcess>
/*
MainWindow::MainWindow(QObject *parent) : QObject(parent)
{

}
*/
void MainWindow::startPicturesApplication()
{
    QString commend="startx";
    qint64 pid;
    QProcess appProcess;
    appProcess.startDetached("sh", QStringList() << "-c" << commend,QProcess::nullDevice(),&pid);

    MainWindow::mainView->close();
    double i = 0;
    int j = 0;
    while(1)
    {
        if(i>99999999)
        {
            j++;
            qDebug() << pid;
            i=0;
            QProcess killProcess;
            killProcess.setProcessChannelMode(QProcess::MergedChannels);
            QString strPid = QString::number(pid);
            QString com = "kill -0 "+strPid;
            killProcess.start(com);

            if (killProcess.waitForFinished())
            {
                QString info = killProcess.readAll();
                if(info.count()>2)
                {
                    MainWindow::mainView->setResizeMode(QQuickView::SizeRootObjectToView);
                    MainWindow::mainView->setSource(QString("qrc:/main.qml"));
                    MainWindow::mainView->show();
                    break;
                }
            }
        }
        i++;
    }
}
