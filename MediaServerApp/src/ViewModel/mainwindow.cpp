#include "mainwindow.h"

#include <QProcess>
#include <QThread>
#include <QTimer>

#include "../screensavermanager.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    bluetoothctl = new Bluetoothctl();
}

void MainWindow::startWeatherApplication()
{
    QProcess appProcess;
    appProcess.startDetached("systemctl", QStringList() << "start"
                                                        << "weather.service");
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

void MainWindow::pairWithBluetoothDevice()
{
    bluetoothctl->pair();
}

void MainWindow::pairAndTrustWithBluetoothDevice()
{
    bluetoothctl->trust();
}

void MainWindow::cancelPairWithBluetoothDevice()
{
    bluetoothctl->cancel();
}

void MainWindow::getPairBluetoothMessage(QObject *messageDialog)
{
    bluetoothctl->setMessageDialog(messageDialog);
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
