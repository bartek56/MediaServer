import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        id: text1
        x: 108
        y: 98
        width: 414
        height: 82
        text: qsTr("Hello World")
        wrapMode: Text.WordWrap
        font.pixelSize: 61
    }

    Button {
        id: button
        x: 255
        y: 308
        text: qsTr("Button")
        autoExclusive: false
    }
}
