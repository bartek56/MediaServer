import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

ToolBar
{
    id: toolBar

    GridLayout
    {
        id: gridLayout
        height: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        rows: 1
        columns: 3
        anchors.verticalCenter: parent.verticalCenter
        Text
        {
            id: tDate
            font
            {
                family: "Comic Sans MS"
                pixelSize: 20
            }
        }
        Text
        {
            id: tClock
            font
            {
                family: "Comic Sans MS"
                pixelSize: 20
            }
            anchors.right: parent.right
         }
     }

    Timer
    {
        interval: 500
        running: true
        repeat: true
        onTriggered:
        {
            var date = new Date()
            tDate.text =  date.toLocaleDateString(Qt.locale("en_US"))
            tClock.text = date.toLocaleTimeString(Qt.locale("en_US"), "hh:mm:ss ap")
        }
    }
}

