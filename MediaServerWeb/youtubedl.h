#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QQuickView>
/*
class DataObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)

};
*/
class Youtubedl : public QObject
{
    Q_OBJECT
public:
    explicit Youtubedl(QObject *parent = nullptr);
    static QQuickView *mainView;
    static void init (QQuickView *obj)
    {
        mainView=obj;
    }

    Q_INVOKABLE void test(QObject *list);

signals:

public slots:
};

#endif // MAIN_H
