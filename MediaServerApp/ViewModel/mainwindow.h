#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtQuick>
#include <memory>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    //static QQuickView mainView;
    static QQuickView *mainView;
    static void init (QQuickView *obj)
    {
        mainView=obj;
    }
    //explicit MainWindow(QObject *parent = nullptr);
    Q_INVOKABLE void startPicturesApplication();

public slots:

private:
};

//MainWindow::mainView=std::make_shared<QQuickView>(s);

#endif // MAINWINDOW_H
