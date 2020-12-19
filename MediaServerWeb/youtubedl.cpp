#include "youtubedl.h"
#include <QDebug>
#include "playlistobjectmodel.h"
#include "playlistobject.h"
#include <qqmlcontext.h>

Youtubedl::Youtubedl(QObject *parent) : QObject(parent)
  ,editHeadersConfigFile(YOUTUBEDL_CONFIGFILE)
{

}
void Youtubedl::loadPlaylists()
{
    vConfigs = editHeadersConfigFile.OpenFile();
    auto iter=vConfigs.begin();
    iter++; // skip Global
    while (iter != vConfigs.end())
    {
        auto map = iter->configs;
        QString name = map.at("name");
        QString link = map.at("link");
        playlistObjectModel->append(new PlaylistObject(name,link));
        iter++;
    }
}
