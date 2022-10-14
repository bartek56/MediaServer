#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QtQuick>
#include "ConfigFile/ScreenSaverConfigFile.h"

class ScreenSaver : public QObject
{
private:
    ScreenSaverConfigFile screenSaverConfigFile;
    VectorData screenSaverConfigs;

    Q_OBJECT
public:
    explicit ScreenSaver(QObject *parent = nullptr);
    Q_INVOKABLE void init(QObject *timer, QObject *folderModel, QObject *screenSaverDialog);
    Q_INVOKABLE void exit();

};

#endif // SCREENSAVER_H
