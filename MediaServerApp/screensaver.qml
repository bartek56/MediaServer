import QtQuick 2.0
import ScreenSaverLib 1.0

MouseArea
{
    ScreenSaver
    {
        id:screenSaver
    }
    propagateComposedEvents: true
    onClicked:
    {
        screenSaver.resetTimer()
    }
}


