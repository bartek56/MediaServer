#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtQuick>
#include <memory>

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
    Q_INVOKABLE void rebootButton_OnClicked();
    Q_INVOKABLE void shutdownButton_OnClicked();

public slots:

};

#endif// MAINWINDOW_H
