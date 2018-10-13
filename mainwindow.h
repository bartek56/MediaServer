#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QDebug>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);

signals:

public slots:
    void bSambaConfig_onClicked();
};

#endif // MAINWINDOW_H
