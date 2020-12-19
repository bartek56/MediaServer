#include <QApplication>
#include <QtQuick>
#include "youtubedl.h"
#include "playlistobjectmodel.h"
#include "playlistobject.h"

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


    PlaylistObjectModel model;
    model.append(new PlaylistObject("relaks","https://relaks"));
    model.append(new PlaylistObject("impreza","https://impreza"));

    QQmlContext *ctxt = view->rootContext();
    ctxt->setContextProperty("myModel", &model);


    view->setSource(QString("qrc:/youtubedl.qml"));

    view->show();

    return app.exec();

}
