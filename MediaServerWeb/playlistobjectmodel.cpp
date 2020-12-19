#include "playlistobjectmodel.h"


PlaylistObjectModel::PlaylistObjectModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void PlaylistObjectModel::registerTypes(const char *uri)
{
    qmlRegisterType<PlaylistObjectModel>(uri, 1, 0, "DataObjectModel");
}

int PlaylistObjectModel::rowCount(const QModelIndex &p) const
{
    Q_UNUSED(p)
    return m_data.size();
}

QVariant PlaylistObjectModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role)
    return QVariant::fromValue(m_data[index.row()]);
}

QHash<int, QByteArray> PlaylistObjectModel::roleNames() const
{
    static QHash<int, QByteArray> *pHash;
    if (!pHash) {
        pHash = new QHash<int, QByteArray>;
        (*pHash)[Qt::UserRole + 1] = "dataObject";
    }
    return *pHash;
}

int PlaylistObjectModel::count() const
{
    return m_data.count();
}

void PlaylistObjectModel::append(QObject *o) {
    int i = m_data.size();
    beginInsertRows(QModelIndex(), i, i);
    m_data.append(o);

    // Emit changed signals
    emit countChanged(count());

    endInsertRows();
}

void PlaylistObjectModel::insert(QObject *o, int i)
{
    beginInsertRows(QModelIndex(), i, i);
    m_data.insert(i, o);
    o->setParent(this);

    // Emit changed signals
    emit countChanged(count());

    endInsertRows();
}

QObject* PlaylistObjectModel::get(int i)
{
    Q_ASSERT(i >= 0 && i <= m_data.count());
    return m_data[i];
}

QQmlListProperty<QObject> PlaylistObjectModel::content()
{
    return QQmlListProperty<QObject>(this,
                                     0,
                                     &PlaylistObjectModel::dataObjectAppend,
                                     &PlaylistObjectModel::dataObjectCount,
                                     &PlaylistObjectModel::dataObjectAt,
                                     &PlaylistObjectModel::dataObjectClear);
}

void PlaylistObjectModel::dataObjectAppend(QQmlListProperty<QObject> *list, QObject *o)
{
    PlaylistObjectModel *dom = qobject_cast<PlaylistObjectModel*>(list->object);
    if (dom && o) {
        dom->m_data.append(o);
    }
}

int PlaylistObjectModel::dataObjectCount(QQmlListProperty<QObject> *list)
{
    PlaylistObjectModel *dom = qobject_cast<PlaylistObjectModel*>(list->object);
    if (dom) {
        return dom->m_data.count();
    }
    return 0;
}

QObject *PlaylistObjectModel::dataObjectAt(QQmlListProperty<QObject> *list, int i)
{
    PlaylistObjectModel *dom = qobject_cast<PlaylistObjectModel*>(list->object);
    if (dom) {
        return dom->m_data.at(i);
    }
    return 0;
}

void PlaylistObjectModel::dataObjectClear(QQmlListProperty<QObject> *list)
{
    PlaylistObjectModel *dom = qobject_cast<PlaylistObjectModel*>(list->object);
    if (dom) {
        dom->m_data.clear();
    }
}
