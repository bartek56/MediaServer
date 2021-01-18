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
#include "ViewModel/settings.h"
#include "ViewModel/multimediaconfig.h"
#include "ViewModel/alarmconfig.h"
#include "ViewModel/alarmview.h"
#include "ViewModel/massstorage.h"
#include "ViewModel/screensaver.h"
#include "ViewModel/napimanager.h"
#include "ViewModel/settingsscreensaver.h"
#include "ViewModel/settingspackages.h"
#include "screensavermanager.h"


QQuickView *MainWindow::mainView;

QTimer *ScreenSaverManager::timer;

bool isItAlarm()
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active alarm.service");
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();

    auto text = process.readAll();
    if(!text.contains("in")) // alarm active
    {
        return true;
    }

    QProcess process2;
    process2.setProcessChannelMode(QProcess::MergedChannels);
    process2.start("bash", QStringList() << "-c" << "systemctl is-active alarm_snooze.service");
    process2.setReadChannel(QProcess::StandardOutput);
    process2.waitForFinished();
    auto text2 = process2.readAll();
    if(!text2.contains("in")) // alarm active
    {
        return true;
    }

    return false;
}



int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQuickView *view = new QQuickView;
    MainWindow::init(view);
    if (view->status() == QQuickView::Error)
        return -1;

    qmlRegisterType<ScreenSaver>("ScreenSaverLib", 1, 0, "ScreenSaver");
    qmlRegisterType<ScreenSaverManager>("ScreenSaverManagerLib", 1, 0, "ScreenSaverManager");
    qmlRegisterType<AlarmConfig>("AlarmConfigLib", 1, 0, "AlarmConfig");
    qmlRegisterType<MultimediaConfig>("MultimediaConfigLib", 1, 0, "MultimediaConfig");
    qmlRegisterType<NapiManager>("NapiManagerLib",1,0,"NapiManager");
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfig");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfig");
    qmlRegisterType<Settings>("SettingsLib", 1, 0, "Settings");
    qmlRegisterType<SettingsScreensaver>("SettingsScreensaverLib", 1, 0, "SettingsScreensaver");
    qmlRegisterType<SettingsPackages>("SettingsPackagesLib", 1, 0, "SettingsPackages");
    qmlRegisterType<MassStorage>("MassStorageLib", 1, 0, "MassStorage");
    qmlRegisterType<AlarmView>("AlarmViewLib", 1, 0, "AlarmView");
    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindow");

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);

    ScreenSaverManager screen;
    screen.Init();

    ScreenSaverHelper screensaverhelper;
    view->rootContext()->setContextProperty("screensaverhelper",&screensaverhelper);

    QObject::connect(ScreenSaverManager::timer, &QTimer::timeout, [&screensaverhelper](){
           emit screensaverhelper.screensavertimeout();
        });


    if(isItAlarm())
        view->setSource(QString("qrc:/alarm.qml"));
    else
        view->setSource(QString("qrc:/main.qml"));

    view->show();

    return app.exec();
}
