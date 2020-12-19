#include "youtubedl.h"
#include <QDebug>
#include "playlistobjectmodel.h"
#include "playlistobject.h"
#include <qqmlcontext.h>

Youtubedl::Youtubedl(QObject *parent) : QObject(parent)
{

}
void Youtubedl::loadPlaylists()
{
    qDebug() << "hello";

    /*
    PlaylistObjectModel model;
    model.append(new PlaylistObject("relaks","https://relaks"));
    model.append(new PlaylistObject("impreza","https://impreza"));

    QQmlContext *ctxt = view->rootContext();
    ctxt->setContextProperty("myModel", &model);
    */

  //  PlaylistObjectModel model;

    playlistObjectModel->append(new PlaylistObject("relaks","https://relaks"));
    playlistObjectModel->append(new PlaylistObject("impreza","https://impreza"));

//    QQmlContext *ctxt = Youtubedl::mainView->rootContext();
//    ctxt->setContextProperty("myModel", &model);
}
