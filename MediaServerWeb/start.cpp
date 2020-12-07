#include <QApplication>
#include <QtQuick>
#include "ViewModel/alarmconfig.h"


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQuickView *view = new QQuickView;
    if (view->status() == QQuickView::Error)
        return -1;

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);

    qmlRegisterType<AlarmConfig>("AlarmConfigLib", 1, 0, "AlarmConfig");

    view->setSource(QString("qrc:/main.qml"));

    view->show();

    return app.exec();

}
