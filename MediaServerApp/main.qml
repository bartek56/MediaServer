import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import MainWindowLib 1.0

Rectangle{

    id: mainRectangle
    visible: true
    width: 800
    height: 480

    Loader {
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        source:"menu.qml";
      }

    Loader {
        id:loaderConfigWindow
      }

    MainWindow
    {
        id:mainWindow
    }

    GridLayout {
        id: gridLayout
        rows: 3
        columns: 4
        anchors.fill: parent

        ToolButton {
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
            text: qsTr("FTP Server")
            font.wordSpacing: 1
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            leftPadding: 6
            onClicked:
            {
                loaderConfigWindow.setSource("ftpConfig.qml")
            }
        }

        ToolButton {
            text: qsTr("DLNA")
            font.wordSpacing: 1
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            onClicked:
            {
                loaderConfigWindow.setSource("dlnaConfig.qml")
            }
        }

        ToolButton {
            text: qsTr("Music Player Daemon")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            onClicked:
            {
                loaderConfigWindow.setSource("mpdConfig.qml")
            }
        }

        ToolButton {
            text: qsTr("Music")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            onClicked:
            {
                mainWindow.startMusicApplication()
            }
        }

        ToolButton {
            text: qsTr("Pictures")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            onClicked:
            {
                mainWindow.startPicturesApplication()
            }
        }


        ToolButton {
            text: qsTr("Video")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            onClicked:
            {

            }
        }

        ToolButton {
            text: qsTr("Settings")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 80
            Layout.preferredWidth: 160
            onClicked:
            {
                loaderConfigWindow.setSource("settings.qml")
            }
        }

    }

}
