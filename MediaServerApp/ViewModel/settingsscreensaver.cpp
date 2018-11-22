#include "settings.h"
#include "mainwindow.h"

void Settings::bScreenSaver_onClicked()
{
    QString commend="startx";
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
