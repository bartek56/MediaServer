#include "playlistobject.h"

PlaylistObject::PlaylistObject(QObject *parent) : QObject(parent)
{
}

PlaylistObject::PlaylistObject(const QString &name, const QString &link, QObject *parent)
    :QObject(parent), m_name(name), m_link(link)
{
}

QString PlaylistObject::name() const
{
    return m_name;
}

void PlaylistObject::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

QString PlaylistObject::link() const
{
    return m_link;
}

void PlaylistObject::setLink(QString link)
{
    if (m_link == link)
        return;

    m_link = link;
    emit linkChanged(m_link);
}
