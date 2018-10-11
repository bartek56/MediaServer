#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_clicked()
{
    auto label = ui->label;
    if(label->isVisible())
    {
        label->setHidden(true);
    }
    else
    {
        label->setHidden(false);
    }
}

