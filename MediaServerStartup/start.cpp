#include <QApplication>
#include <QtQuick>
#include <QQmlContext>
#include "ViewModel/MainWindow.h"
#include "ViewModel/Settings/SettingsIpAddress.h"
#include "ViewModel/Settings/SettingsWifi.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);
    QQuickView *view = new QQuickView;
    view->rootContext()->setContextProperty("qtMajorVersion", QT_VERSION_MAJOR);
    if(view->status() == QQuickView::Error)
        return -1;

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);

    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindow");
    qmlRegisterType<SettingsWifi>("SettingsWifiLib", 1, 0, "SettingsWifi");
    qmlRegisterType<SettingsIpAddress>("SettingsIpAddressLib", 1, 0, "SettingsIpAddress");

    view->setSource(QString("qrc:/main.qml"));

    view->show();

    return app.exec();
}
