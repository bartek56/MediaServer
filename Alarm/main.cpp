#include "ViewModel/AlarmView.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQuickView view;
    if(view.status() == QQuickView::Error)
        return -1;

    qmlRegisterType<AlarmView>("AlarmViewLib", 1, 0, "AlarmView");
    QObject::connect((QObject *) view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    view.setWidth(800);
    view.setHeight(480);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QString("qrc:/main.qml"));
    view.show();


    return app.exec();
}
