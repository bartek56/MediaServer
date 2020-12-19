#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QQuickView>

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
