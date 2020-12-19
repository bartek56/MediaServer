#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QQuickView>
#include "playlistobjectmodel.h"

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

signals:

public slots:
};

#endif // MAIN_H
