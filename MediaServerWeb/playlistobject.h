#ifndef PLAYLISTOBJECT_H
#define PLAYLISTOBJECT_H

#include <QObject>

class PlaylistObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString link READ link WRITE setLink NOTIFY linkChanged)

private:
    QString m_name;
    QString m_link;

public:
    PlaylistObject(QObject *parent = 0);
    PlaylistObject(const QString &name, const QString &link, QObject *parent=0);
    QString name() const;
    QString link() const;

public slots:
    void setLink(QString link);
    void setName(QString name);

signals:
    void nameChanged(QString name);
    void linkChanged(QString link);
};

#endif // PLAYLISTOBJECT_H
