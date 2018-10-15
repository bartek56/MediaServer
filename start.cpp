#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "editfile.h"
#include <mainwindow.h>
#include <QtQuickControls2/QtQuickControls2>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication app(argc, argv);
    //QQuickView view(QString("qrc:/basic-b2qt.qml"));
    QQuickView view(QString("qrc:/main.qml"));
    if (view.status() == QQuickView::Error)
        return -1;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    MainWindow mainWindow;
    view.rootContext()->setContextProperty("g_mainWindow",&mainWindow);
    view.show();

    return app.exec();
}

