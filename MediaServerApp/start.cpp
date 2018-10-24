#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "editfile.h"
#include <ViewModel/mainwindow.h>
#include "ViewModel/sambaconfig.h"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QGuiApplication app(argc, argv);
    QQuickView view(QString("qrc:/main.qml"));
    if (view.status() == QQuickView::Error)
        return -1;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    qmlRegisterType<SambaConfig>("SambaConfigLib", 1, 0, "SambaConfig");
    view.show();

    return app.exec();
}

