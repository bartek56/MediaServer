#include "MainWindow.h"

#include <QProcess>
#include <QThread>
#include <QTimer>

#include "ViewModel/ScreenSaver/ScreenSaverManager.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
}

void MainWindow::startWeatherApplication()
{
    // not supported
}

void MainWindow::startMusicApplication()
{
    QProcess appProcess;
    appProcess.startDetached("systemctl", QStringList() << "start"
                                                        << "mpc_mediaserver.service");
}

void MainWindow::startBrowser()
{
}

void MainWindow::rebootButton_OnClicked()
{
    QProcess appProcess;
    appProcess.startDetached("sh", QStringList() << "-c"
                                                 << "reboot");
}

void MainWindow::shutdownButton_OnClicked()
{
    QProcess appProcess;
    appProcess.startDetached("sh", QStringList() << "-c"
                                                 << "poweroff");
}
