#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QQuickView>
#include "playlistobjectmodel.h"
#include "editheadersconfigfile.h"

class Youtubedl : public QObject
{
    Q_OBJECT
public:
    explicit Youtubedl(QObject *parent = nullptr);
    static PlaylistObjectModel *playlistObjectModel;
    static void initPlaylist (PlaylistObjectModel *obj)
    {
        playlistObjectModel=obj;
    }

    Q_INVOKABLE void loadPlaylists();
    Q_INVOKABLE void save();

    Q_INVOKABLE void addNewPlaylist(const QString playlistName, const QString link);
    Q_INVOKABLE void removePlaylist(const int index, const QString playlistName);


private:
    const QString YOUTUBEDL_CONFIGFILE = "/etc/mediaserver/youtubedl.ini";
    EditHeadersConfigFile editHeadersConfigFile;
    std::vector<HeadersConfig> vConfigs;
};

#endif // MAIN_H
