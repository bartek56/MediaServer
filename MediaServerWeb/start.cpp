#include <QApplication>
#include <QtQuick>
#include "youtubedl.h"
#include "dataobjectmodel.h"

QQuickView *Youtubedl::mainView;


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQuickView *view = new QQuickView;
    if (view->status() == QQuickView::Error)
        return -1;
    Youtubedl::init(view);

    view->setWidth(800);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);

    qmlRegisterType<Youtubedl>("YoutubeLib", 1, 0, "Youtubedl");




    view->setSource(QString("qrc:/youtubedl.qml"));

    view->show();

    return app.exec();

}
