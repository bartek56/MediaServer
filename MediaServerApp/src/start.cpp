#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QApplication>
#include <QtQuick>
#include <QObject>
#include <QThread>
#include "ViewModel/mainwindow.h"
#include "ViewModel/sambaconfig.h"
#include "ViewModel/ftpconfig.h"
#include "src/ViewModel/settings.h"
#include "ViewModel/multimediaconfig.h"
#include "src/ViewModel/alarmconfig.h"
#include "ViewModel/massstorage.h"
#include "ViewModel/screensaver.h"
#include "ViewModel/napimanager.h"
#include "ViewModel/settingsscreensaver.h"
#include "ViewModel/settingspackages.h"
#include "ViewModel/quotes.h"
#include "screensavermanager.h"


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
    qmlRegisterType<Settings>("SettingsLib", 1, 0, "Settings");
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
