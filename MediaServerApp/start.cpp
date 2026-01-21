#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuick>
#include <QObject>
#include <QDBusConnection>
#include <QDBusMessage>
#include "ViewModel/MainWindow/MainWindow.h"
#include "ViewModel/MainWindow/BluetoothAgent.h"
#include "ViewModel/Samba/SambaConfig.h"
#include "ViewModel/FtpConfig.h"
#include "ViewModel/Settings/SettingsIpAddress.h"
#include "ViewModel/Settings/SettingsStatus.h"
#include "ViewModel/Settings/SettingsWifi.h"
#include "ViewModel/MultimediaConfig.h"
#include "ViewModel/AlarmConfig.h"
#include "ViewModel/MassStorage.h"
#include "ViewModel/ScreenSaver/ScreenSaver.h"
#include "ViewModel/NapiManager.h"
#include "ViewModel/Settings/SettingsScreenSaver.h"
#include "ViewModel/Settings/SettingsPackages.h"
#include "ViewModel/ScreenSaver/ScreenSaverManager.h"


QQuickView *MainWindow::mainView;
QTimer *ScreenSaverManager::timer;

int main(int argc, char *argv[])
{
    // App
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("MediaServer");
    QCoreApplication::setOrganizationDomain("MediaServer");
    QCoreApplication::setApplicationName("Media Server");


    // Main Window
    QQuickView *view = new QQuickView;
    MainWindow::init(view);
    if(view->status() == QQuickView::Error)
        return -1;

    qmlRegisterType<AlarmConfig>("AlarmConfigLib", 1, 0, "AlarmConfigView");
    qmlRegisterType<MultimediaConfig>("MultimediaConfigLib", 1, 0, "MultimediaConfigView");
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfigView");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfigView");

    qmlRegisterType<NapiManager>("NapiManagerLib", 1, 0, "NapiManagerView");

    qmlRegisterType<SettingsStatus>("SettingsStatusLib", 1, 0, "SettingsStatusView");
    qmlRegisterType<SettingsWifi>("SettingsWifiLib", 1, 0, "SettingsWifiView");
    qmlRegisterType<SettingsIpAddress>("SettingsIpAddressLib", 1, 0, "SettingsIpAddressView");
    qmlRegisterType<SettingsScreensaver>("SettingsScreensaverLib", 1, 0, "SettingsScreensaverView");
    qmlRegisterType<SettingsPackages>("SettingsPackagesLib", 1, 0, "SettingsPackagesView");

    qmlRegisterType<MassStorage>("MassStorageLib", 1, 0, "MassStorageView");

    qmlRegisterType<ScreenSaverManager>("ScreenSaverManagerLib", 1, 0, "ScreenSaverManagerView");
    qmlRegisterType<ScreenSaver>("ScreenSaverLib", 1, 0, "ScreenSaverView");

    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindowView");

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);


    // Screensaver
    ScreenSaverHelper screensaverhelper;
    view->rootContext()->setContextProperty("screensaverhelper", &screensaverhelper);

    ScreenSaverManager screen;
    const bool resultInit = screen.Init();

    if(resultInit)
    {
        QObject::connect(ScreenSaverManager::timer, &QTimer::timeout, [&screensaverhelper]() { emit screensaverhelper.screensavertimeout(); });
    }


    // Bluetooth
    QDBusConnection bus = QDBusConnection::systemBus();
    BluetoothAgent agent;
    bool isDbusBtConnection = bus.isConnected();
    if (!isDbusBtConnection) {
        qCritical() << "Cannot connect to system bus";
    }
    else
    {
        bus.registerObject(AGENT_PATH, &agent, QDBusConnection::ExportAllSlots);

        QDBusMessage registerAgent = QDBusMessage::createMethodCall(
                "org.bluez", "/org/bluez", "org.bluez.AgentManager1", "RegisterAgent");
        registerAgent << QDBusObjectPath(AGENT_PATH) << "KeyboardDisplay";
        bus.call(registerAgent);

        QDBusMessage requestDefault = QDBusMessage::createMethodCall(
                "org.bluez", "/org/bluez", "org.bluez.AgentManager1", "RequestDefaultAgent");
        requestDefault << QDBusObjectPath(AGENT_PATH);
        bus.call(requestDefault);

        view->rootContext()->setContextProperty("btAgent", &agent);
    }

    view->setSource(QString("qrc:/main.qml"));
    view->show();

    return app.exec();
}
