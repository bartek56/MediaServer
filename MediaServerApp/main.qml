import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import MainWindowLib 1.0


Rectangle{

    id: mainRectangle
    visible: true
    width: 800
    height: 480

    Timer
    {
        id: screenSaverTimer
        interval: 45000 //45sec
        running: true
        onTriggered:
        {
            mainWindow.startScreensaver()
        }
    }

    MouseArea
    {
        anchors.fill: parent
     // Pass mouse events through
        propagateComposedEvents: true
        onClicked: { screenSaverTimer.restart(); mouse.accepted = false }
    }
    Loader {
        anchors.topMargin: 0
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

    Column {
        id: column
        x: 0
        y: 57
        width: 800
        height: 423
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.top: parent.top

        RowLayout {
            id: rowLayout
            anchors.rightMargin: 16
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 22
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 229
            anchors.top: parent.top
            anchors.topMargin: 61

            ToolButton {
                id: toolButton
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 120
                Layout.preferredWidth: 200
                Image {
                    id: gmpcImage
                    x: 37
                    y: 0
                    width: 116
                    height: 97
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/gmpc.svg"
                }
                Text {
                    id: gmpcText
                    x: 81
                    y: 94
                    width: 50
                    height: 26
                    text: qsTr("Music")
                    font.letterSpacing: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 17
                }

                onClicked:
                {
                    mainWindow.startMusicApplication()
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 120
                Layout.preferredWidth: 200
                Image {
                    id: gqviewImage
                    x: 37
                    y: 0
                    width: 116
                    height: 97
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/gqview.png"
                }
                Text {
                    id: gqviewText
                    x: 81
                    y: 94
                    width: 50
                    height: 26
                    text: qsTr("Pictures")
                    font.letterSpacing: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 17
                }
                onClicked:
                {
                    mainWindow.startPicturesApplication()
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 120
                Layout.preferredWidth: 200

                Image {
                    id: webBrowserImage
                    x: 37
                    y: 0
                    width: 102
                    height: 97
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/browser.png"
                }
                Text {
                    id: webBrowserText
                    x: 81
                    y: 94
                    width: 50
                    height: 26
                    text: qsTr("Web Browser")
                    font.letterSpacing: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 17
                }
                onClicked:
                {
                    mainWindow.startWebBrowser()
                }

            }

        }

        RowLayout {
            id: rowLayout1
            height: 100
            anchors.rightMargin: 10
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 18
            spacing: 10.7
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 54

            ToolButton {
                //autoExclusive: true
                //font.wordSpacing: 1
                //font.letterSpacing: 1
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Image {
                    id: sambaImage
                    x: 37
                    y: 6
                    width: 76
                    height: 64
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/samba.png"
                }
                Text {
                    id: sambaText
                    x: 81
                    y: 72
                    width: 50
                    height: 26
                    text: qsTr("Samba")
                    font.letterSpacing: 1
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    loaderConfigWindow.setSource("sambaConfig.qml")
                }
            }

            ToolButton {
                font.wordSpacing: 1
                font.letterSpacing: 1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                leftPadding: 6
                Image {
                    id: ftpImage
                    x: 37
                    y: 0
                    width: 76
                    height: 75
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/ftp.png"
                }
                Text {
                    id: ftpText
                    x: 81
                    y: 74
                    width: 50
                    height: 26
                    text: qsTr("FTP")
                    font.letterSpacing: 1
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    loaderConfigWindow.setSource("ftpConfig.qml")
                }
            }

            ToolButton {
                font.wordSpacing: 1
                font.letterSpacing: 1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                Image {
                    id: dlnaImage
                    x: 37
                    y: 0
                    width: 88
                    height: 74
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/dlna.png"
                }
                Text {
                    id: dlnaText
                    x: 81
                    y: 74
                    width: 50
                    height: 26
                    text: qsTr("DLNA")
                    font.letterSpacing: 1
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    loaderConfigWindow.setSource("dlnaConfig.qml")
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                Image {
                    id: mpdImage
                    x: 37
                    y: 0
                    width: 78
                    height: 68
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/mpd.png"
                }
                Text {
                    id: mpdText
                    x: 81
                    y: 74
                    width: 50
                    height: 26
                    text: qsTr("MPD")
                    font.letterSpacing: 1
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    loaderConfigWindow.setSource("mpdConfig.qml")
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110

                Image {
                    id: fileBrowserImage
                    x: 37
                    y: 0
                    width: 68
                    height: 67
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/pcmanfm.png"
                }
                Text {
                    id: fileBrowserText
                    x: 81
                    y: 73
                    width: 50
                    height: 26
                    text: qsTr("Browser")
                    anchors.horizontalCenterOffset: 0
                    font.letterSpacing: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    mainWindow.startBrowser()
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                Image {
                    id: settingsImage
                    x: 37
                    y: 0
                    width: 68
                    height: 63
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/settings.png"
                }
                Text {
                    id: settingsText
                    x: 81
                    y: 74
                    width: 50
                    height: 26
                    text: qsTr("Settings")
                    font.letterSpacing: 1
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    loaderConfigWindow.setSource("settings.qml")
                }
            }
        }
    }

}

/*##^## Designer {
    D{i:15;anchors_height:100;anchors_width:100}D{i:14;anchors_height:100;anchors_width:100}
}
 ##^##*/
