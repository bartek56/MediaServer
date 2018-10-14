#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{

}

void MainWindow::bSave_onClicked(QString text)
{
    qDebug() << "Clicked "+text;

}
