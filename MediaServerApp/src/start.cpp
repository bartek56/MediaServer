#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuick>
#include <QObject>
#include "ViewModel/MainWindow.h"
#include "ViewModel/SambaConfig.h"
#include "ViewModel/FtpConfig.h"
#include "src/ViewModel/SettingsIpAddress.h"
#include "src/ViewModel/SettingsStatus.h"
#include "src/ViewModel/SettingsWifi.h"
#include "ViewModel/MultimediaConfig.h"
#include "src/ViewModel/AlarmConfig.h"
#include "ViewModel/MassStorage.h"
#include "ViewModel/ScreenSaver.h"
#include "ViewModel/NapiManager.h"
#include "ViewModel/SettingsScreenSaver.h"
#include "ViewModel/SettingsPackages.h"
#include "ViewModel/Quotes.h"
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

    qmlRegisterType<ScreenSaver>("ScreenSaverLib", 1, 0, "ScreenSaver");
    qmlRegisterType<ScreenSaverManager>("ScreenSaverManagerLib", 1, 0, "ScreenSaverManager");
    qmlRegisterType<AlarmConfig>("AlarmConfigLib", 1, 0, "AlarmConfig");
    qmlRegisterType<MultimediaConfig>("MultimediaConfigLib", 1, 0, "MultimediaConfig");
    qmlRegisterType<NapiManager>("NapiManagerLib", 1, 0, "NapiManager");
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfig");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfig");
    qmlRegisterType<SettingsStatus>("SettingsStatusLib", 1, 0, "SettingsStatus");
    qmlRegisterType<SettingsWifi>("SettingsWifiLib", 1, 0, "SettingsWifi");
    qmlRegisterType<SettingsIpAddress>("SettingsIpAddressLib", 1, 0, "SettingsIpAddress");
    qmlRegisterType<SettingsScreensaver>("SettingsScreensaverLib", 1, 0, "SettingsScreensaver");
    qmlRegisterType<SettingsPackages>("SettingsPackagesLib", 1, 0, "SettingsPackages");
    qmlRegisterType<MassStorage>("MassStorageLib", 1, 0, "MassStorage");
    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindow");
    qmlRegisterType<Quotes>("QuotesLib", 1, 0, "Quotes");

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);

    ScreenSaverManager screen;
    screen.Init();

    ScreenSaverHelper screensaverhelper;
    view->rootContext()->setContextProperty("screensaverhelper", &screensaverhelper);

    QObject::connect(ScreenSaverManager::timer, &QTimer::timeout, [&screensaverhelper]() { emit screensaverhelper.screensavertimeout(); });

    view->setSource(QString("qrc:/main.qml"));
    view->show();

    return app.exec();
}
