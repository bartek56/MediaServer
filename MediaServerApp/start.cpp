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
#include "ViewModel/alarmview.h"
#include "screensaver.h"

QQuickView *MainWindow::mainView;

QTimer *ScreenSaver::timer;

bool isItAlarm()
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active cron.service");
    process.setReadChannel(QProcess::StandardOutput);
    QStringList devicesList;
    process.waitForFinished();
    auto text = process.readAll();
    if(!text.contains("in")) // alarm active
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

    qmlRegisterType<MpdConfig>("MpdConfigLib", 1, 0, "MpdConfig");
    qmlRegisterType<DlnaConfig>("DlnaConfigLib", 1, 0, "DlnaConfig");
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfig");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfig");
    qmlRegisterType<Settings>("SettingsLib", 1, 0, "Settings");
    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindow");
    qmlRegisterType<AlarmView>("AlarmViewLib", 1, 0, "AlarmView");
    qmlRegisterType<ScreenSaver>("ScreenSaverLib", 1, 0, "ScreenSaver");

    view->setResizeMode(QQuickView::SizeRootObjectToView);

    if(isItAlarm())
    {
        view->setSource(QString("qrc:/alarm.qml"));
    }
    else
    {
        view->setSource(QString("qrc:/main.qml"));
    }

    view->show();

    ScreenSaver screen;
    screen.Init();

    QString commend2 = "/opt/start2.sh 999999";
    qint64 pid2;
    QProcess appProcess2;
    appProcess2.startDetached("sh", QStringList() << "-c" << commend2,QProcess::nullDevice(),&pid2);

    return app.exec();
}

