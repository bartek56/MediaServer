#include "ViewModel/AlarmView.h"
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);

    QQuickView view;
    view.rootContext()->setContextProperty("qtMajorVersion", QT_VERSION_MAJOR);
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
