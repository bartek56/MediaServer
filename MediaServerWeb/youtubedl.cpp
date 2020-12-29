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

void Youtubedl::save()
{
    editHeadersConfigFile.SaveFile(vConfigs);
}

void Youtubedl::addNewPlaylist(const QString playlistName, const QString link)
{
   std::map<QString, QString> mConfigsParameters;
   mConfigsParameters.insert(std::make_pair("name",playlistName));
   mConfigsParameters.insert(std::make_pair("link",link));
   vConfigs.push_back(HeadersConfig("["+playlistName+"]",mConfigsParameters));
   playlistObjectModel->append(new PlaylistObject(playlistName,link));
}

void Youtubedl::removePlaylist(const int index, const QString playlistName)
{
    for (auto it = vConfigs.begin(); it != vConfigs.end(); ++it)
    {
        QString temp = it->name;
        QString header = temp;
        header.remove(header.length()-1,1);
        header.remove(0,1);

        if(header==playlistName)
        {
            vConfigs.erase(it);
            break;
        }
    }
    playlistObjectModel->remove(index);
}
