#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QDebug>
#include <QtQuick>
#include <QQmlComponent>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);

public slots:
    void bSave_onClicked(QString text);

};

#endif // MAINWINDOW_H
