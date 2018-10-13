import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {

    visible: true
    width: 800
    height: 480
    title: qsTr("Raspberry Pi 3")

    Loader {
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        source:"menu.qml";
      }

}
