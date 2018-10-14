import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3



ApplicationWindow{

    id: mainWindow
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

    Loader {
        id:loaderConfigWindow
      }


    GridLayout {
        id: gridLayout
        rows: 3
        columns: 3
        anchors.fill: parent

        ToolButton {
            id: bSambaConfig
            text: qsTr("Samba")
            autoExclusive: true
            font.wordSpacing: 1
            font.letterSpacing: 1
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked:
            {
                loaderConfigWindow.setSource("sambaConfig.qml")
            }

        }

        ToolButton {
            id: bVsftpConfig
            text: qsTr("FTP Server")
            font.wordSpacing: 1
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            leftPadding: 6
        }

        ToolButton {
            id: toolButton3
            text: qsTr("Tool Button")
            font.wordSpacing: 1
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
        }

        ToolButton {
            id: toolButton4
            text: qsTr("Tool Button")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
        }

        ToolButton {
            id: toolButton5
            text: qsTr("Tool Button")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
        }

        ToolButton {
            id: toolButton6
            text: qsTr("Tool Button")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
        }
    }
}
