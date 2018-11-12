#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuick>
#include "editsambaconfigfile.h"
#include "ViewModel/mainwindow.h"
#include "ViewModel/sambaconfig.h"
#include "ViewModel/ftpconfig.h"
#include "ViewModel/settings.h"

QQuickView *MainWindow::mainView;

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication app(argc, argv);
    //QGuiApplication app(argc, argv);
    //QQuickView view;
    //std::make_shared<QQuickView>();
    QQuickView *view = new QQuickView;
    MainWindow::init(view);
    if (view->status() == QQuickView::Error)
        return -1;

    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfig");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfig");
    qmlRegisterType<Settings>("SettingsLib", 1, 0, "Settings");
    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindow");

    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QString("qrc:/main.qml"));
    view->show();
    return app.exec();
}

