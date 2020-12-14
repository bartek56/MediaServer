#include <QApplication>
#include <QtQuick>
#include "mainwindow.h"
#include "ViewModel/settings.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQuickView *view = new QQuickView;
    if (view->status() == QQuickView::Error)
        return -1;

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);

    qmlRegisterType<MainWindow>("MainWindowLib", 1, 0, "MainWindow");
    qmlRegisterType<Settings>("SettingsLib", 1, 0, "Settings");

    view->setSource(QString("qrc:/main.qml"));

    view->show();

    return app.exec();
}
