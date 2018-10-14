#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "editfile.h"
#include <mainwindow.h>

int main(int argc, char *argv[])
{
/*
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication app(argc, argv);
    MainWindow mainWindow;

    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("g_mainWindow",&mainWindow);
    engine.load(QUrl(QStringLiteral("qrc:/basic-b2qt.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
    */
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);
    QQuickView view(QString("qrc:/basic-b2qt.qml"));
    if (view.status() == QQuickView::Error)
        return -1;
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    view.show();

    return app.exec();
}

