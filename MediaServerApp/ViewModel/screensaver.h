#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QtQuick>
#include "editscreensaverconfigfile.h"

class ScreenSaver : public QObject
{
private:
    EditScreenSaverConfigFile editScreenSaverConfigFile;
    std::map<QString,QString> mConfigsParameters;

    Q_OBJECT
public:
    explicit ScreenSaver(QObject *parent = nullptr);
    Q_INVOKABLE void init(QObject *timer, QObject *folderModel, QObject *screenSaverDialog);
    Q_INVOKABLE void exit();

};

#endif // SCREENSAVER_H
