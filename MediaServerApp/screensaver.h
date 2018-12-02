#ifndef SCREENSAVER_H
#define SCREENSAVER_H
#include <QTimer>
#include <QObject>
#include "editscreensaverconfigfile.h"

class ScreenSaver : public QObject
{
    Q_OBJECT
public:
    explicit ScreenSaver(QObject *parent = nullptr);
    static QTimer *timer;
    void Init();
    Q_INVOKABLE void resetTimer();
signals:

public slots:
    void startScreen();
private:

    EditScreenSaverConfigFile editScreenSaverConfigFile;
};

#endif // SCREENSAVER_H
