#ifndef SCREENSAVERMANAGER_H
#define SCREENSAVERMANAGER_H
#include <QTimer>
#include <QObject>
#include "ConfigFile/ScreenSaverConfigFile.h"

class ScreenSaverManager : public QObject
{
    Q_OBJECT
public:
    explicit ScreenSaverManager(QObject *parent = nullptr);
    static QTimer *timer;
    bool Init();
    Q_INVOKABLE void resetTimer();
signals:

private:
    ScreenSaverConfigFile screenSaverConfigFile;
};

class ScreenSaverHelper : public QObject
{

    Q_OBJECT
public:
    using QObject::QObject;
signals:
    void screensavertimeout();
};


#endif
