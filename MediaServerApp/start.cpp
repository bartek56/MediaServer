#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuick>
#include <QObject>
#include "ViewModel/MainWindow.h"
#include "ViewModel/SambaConfig.h"
#include "ViewModel/FtpConfig.h"
#include "ViewModel/SettingsIpAddress.h"
#include "ViewModel/SettingsStatus.h"
#include "ViewModel/SettingsWifi.h"
#include "ViewModel/MultimediaConfig.h"
#include "ViewModel/AlarmConfig.h"
#include "ViewModel/MassStorage.h"
#include "ViewModel/ScreenSaver.h"
#include "ViewModel/NapiManager.h"
#include "ViewModel/SettingsScreenSaver.h"
#include "ViewModel/SettingsPackages.h"
#include "ScreenSaverManager.h"


QQuickView *MainWindow::mainView;
QTimer *ScreenSaverManager::timer;

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("MediaServer");
    QCoreApplication::setOrganizationDomain("MediaServer");
    QCoreApplication::setApplicationName("Media Server");
    QQuickView *view = new QQuickView;
    MainWindow::init(view);
    if(view->status() == QQuickView::Error)
        return -1;

    qmlRegisterType<ScreenSaver>("ScreenSaverLib", 1, 0, "ScreenSaverView");
    qmlRegisterType<ScreenSaverManager>("ScreenSaverManagerLib", 1, 0, "ScreenSaverManagerView");
    qmlRegisterType<AlarmConfig>("AlarmConfigLib", 1, 0, "AlarmConfigView");
    qmlRegisterType<MultimediaConfig>("MultimediaConfigLib", 1, 0, "MultimediaConfigView");
    qmlRegisterType<NapiManager>("NapiManagerLib", 1, 0, "NapiManagerView");
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfigView");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfigView");
    qmlRegisterType<SettingsStatus>("SettingsStatusLib", 1, 0, "SettingsStatusView");
    qmlRegisterType<SettingsWifi>("SettingsWifiLib", 1, 0, "SettingsWifiView");
    qmlRegisterType<SettingsIpAddress>("SettingsIpAddressLib", 1, 0, "SettingsIpAddressView");
    qmlRegisterType<SettingsScreensaver>("SettingsScreensaverLib", 1, 0, "SettingsScreensaverView");
    qmlRegisterType<SettingsPackages>("SettingsPackagesLib", 1, 0, "SettingsPackagesView");
    qmlRegisterType<MassStorage>("MassStorageLib", 1, 0, "MassStorageView");
    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindowView");

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);


    ScreenSaverHelper screensaverhelper;
    view->rootContext()->setContextProperty("screensaverhelper", &screensaverhelper);

    ScreenSaverManager screen;
    const bool resultInit = screen.Init();

    if(resultInit)
    {
        QObject::connect(ScreenSaverManager::timer, &QTimer::timeout, [&screensaverhelper]() { emit screensaverhelper.screensavertimeout(); });
    }

    view->setSource(QString("qrc:/main.qml"));
    view->show();

    return app.exec();
}
