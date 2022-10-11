import QtQuick 2.0
import ScreenSaverManagerLib 1.0

MouseArea
{
    ScreenSaverManagerView
    {
        id:screensavermanager
    }
    propagateComposedEvents: true
    onClicked:
    {
        screensavermanager.resetTimer()
    }
}
