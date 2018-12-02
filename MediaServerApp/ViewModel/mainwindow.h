#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtQuick>
#include <memory>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    static QQuickView *mainView;
    static void init (QQuickView *obj)
    {
        mainView=obj;
    }
    explicit MainWindow(QObject *parent = nullptr);
    Q_INVOKABLE void startPicturesApplication();
    Q_INVOKABLE void startMusicApplication();
    Q_INVOKABLE void startVideoApplication();
    Q_INVOKABLE void startWebBrowser();
    Q_INVOKABLE void startBrowser();

public slots:

private:
    void startApplication(QString commend);
};

#endif // MAINWINDOW_H
