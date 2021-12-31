#include "mainwindow.h"

#include <QProcess>
#include <QThread>
#include <QTimer>

#include "../screensavermanager.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    bluetoothctl= new Bluetoothctl();
}

void MainWindow::startPicturesApplication()
{
}

void MainWindow::startMusicApplication()
{
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
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c"
                                                  << "reboot");
}

void MainWindow::shutdownButton_OnClicked()
{
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c"
                                                  << "poweroff");
}
