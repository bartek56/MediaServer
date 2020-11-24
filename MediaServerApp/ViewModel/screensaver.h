#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QObject>

class ScreenSaver : public QObject
{
    Q_OBJECT
public:
    explicit ScreenSaver(QObject *parent = nullptr);
    Q_INVOKABLE void init();
    Q_INVOKABLE void exit();

signals:

public slots:
};

#endif // SCREENSAVER_H
