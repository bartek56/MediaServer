#include "mainwindow.h"
#include "../screensavermanager.h"
#include <QProcess>
#include <QTimer>
#include <QThread>


MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    bluetoothctl = new Bluetoothctl();
}

void MainWindow::startPicturesApplication()
{
    QProcess::startDetached("systemctl", QStringList() << "-c" << "start gqview.service");
    QProcess::startDetached("systemctl", QStringList() << "-c" << "stop start.service");
}

void MainWindow::startMusicApplication()
{
    QProcess::startDetached("systemctl", QStringList() << "-c" << "start gmpc.service");
    QProcess::startDetached("systemctl", QStringList() << "-c" << "stop start.service");
}

void MainWindow::startBrowser()
{
    QProcess::startDetached("systemctl", QStringList() << "-c" << "start pcmanfm.service");
    QProcess::startDetached("systemctl", QStringList() << "-c" << "stop start.service");
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
    appProcess2.startDetached("sh", QStringList() << "-c" << "reboot");
}

void MainWindow::shutdownButton_OnClicked()
{
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << "poweroff");
}

