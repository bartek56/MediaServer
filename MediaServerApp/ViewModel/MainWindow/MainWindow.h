#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtQuick>
#include <memory>
#include "Bluetoothctl.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    static QQuickView *mainView;
    static void init(QQuickView *obj)
    {
        mainView = obj;
    }
    explicit MainWindow(QObject *parent = nullptr);
    Q_INVOKABLE void startWeatherApplication();
    Q_INVOKABLE void startMusicApplication();
    Q_INVOKABLE void startBrowser();
    Q_INVOKABLE void pairWithBluetoothDevice();
    Q_INVOKABLE void pairAndTrustWithBluetoothDevice();
    Q_INVOKABLE void cancelPairWithBluetoothDevice();
    Q_INVOKABLE void getPairBluetoothMessage(QObject *messageDialog);
    Q_INVOKABLE void rebootButton_OnClicked();
    Q_INVOKABLE void shutdownButton_OnClicked();


public slots:

private:
    Bluetoothctl *bluetoothctl;
};

#endif// MAINWINDOW_H
