#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuick>
#include "editsambaconfigfile.h"
#include "ViewModel/mainwindow.h"
#include "ViewModel/sambaconfig.h"
#include "ViewModel/ftpconfig.h"
#include "ViewModel/settings.h"
#include "ViewModel/dlnaconfig.h"
#include "ViewModel/mpdconfig.h"

QQuickView *MainWindow::mainView;

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQuickView *view = new QQuickView;
    MainWindow::init(view);
    if (view->status() == QQuickView::Error)
        return -1;

    qmlRegisterType<MpdConfig>("MpdConfigLib", 1, 0, "MpdConfig");
    qmlRegisterType<DlnaConfig>("DlnaConfigLib", 1, 0, "DlnaConfig");
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfig");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfig");
    qmlRegisterType<Settings>("SettingsLib", 1, 0, "Settings");
    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindow");


    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QString("qrc:/main.qml"));
    view->show();
    return app.exec();
}

