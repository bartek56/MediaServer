#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QtQuick>
#include "editsambaconfigfile.h"
#include "ViewModel/mainwindow.h"
#include "ViewModel/sambaconfig.h"
#include "ViewModel/ftpconfig.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication app(argc, argv);
    QQuickView view;
    if (view.status() == QQuickView::Error)
        return -1;
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfig");
    qmlRegisterType<FtpConfig>("FtpConfigLib", 1, 0, "FtpConfig");

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QString("qrc:/main.qml"));

    view.show();

    return app.exec();
}

