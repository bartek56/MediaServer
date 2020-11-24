#include "screensaver.h"
#include "screensavermanager.h"

ScreenSaver::ScreenSaver(QObject *parent) : QObject(parent)
{

}

void ScreenSaver::init()
{
    ScreenSaverManager::timer->stop();
}

void ScreenSaver::exit()
{
    ScreenSaverManager::timer->start();
}
