#include "mainwindow.h"
#include "screensavermanager.h"
#include <QProcess>
#include <QTimer>
#include <QThread>


MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    bluetoothctl = new Bluetoothctl();
}

void MainWindow::startPicturesApplication()
{
    QProcess::startDetached("systemctl start gqview.service");
    QProcess::startDetached("systemctl stop start.service");
}

void MainWindow::startMusicApplication()
{
    QProcess::startDetached("systemctl start gmpc.service");
    QProcess::startDetached("systemctl stop start.service");
}

void MainWindow::startBrowser()
{
    QProcess::startDetached("systemctl start pcmanfm.service");
    QProcess::startDetached("systemctl stop start.service");
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

void MainWindow::shutdownButton_OnClicked()
{
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << "poweroff");
}

