#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QQuickView>
#include "playlistobjectmodel.h"
#include "editheadersconfigfile.h"
#include "ViewModel/settings.h"

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

    Q_INVOKABLE void checkStatus(QObject *autoStartupSwitch);

    Q_INVOKABLE void loadPlaylists();
    Q_INVOKABLE void save();

    Q_INVOKABLE void addNewPlaylist(const QString playlistName, const QString link);
    Q_INVOKABLE void removePlaylist(const QString playlistName);
    Q_INVOKABLE void startDownload(QObject *bStartDownload);
    Q_INVOKABLE void autoStartupSwitch_OnClicked(bool autoStartupIsEnable);




private:
    const QString YOUTUBEDL_CONFIGFILE = "/etc/mediaserver/youtubedl.ini";
    EditHeadersConfigFile editHeadersConfigFile;
    std::vector<HeadersConfig> vConfigs;
    Settings settings;
};

#endif // MAIN_H
