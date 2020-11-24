import QtQuick 2.0
import ScreenSaverManagerLib 1.0

MouseArea
{
    ScreenSaverManager
    {
        id:screensavermanager
    }
    propagateComposedEvents: true
    onClicked:
    {
        screensavermanager.resetTimer()
    }
}


