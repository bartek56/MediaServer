import QtQuick 2.9
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import MainWindowLib 1.0
import QtQuick.Dialogs 1.1


Rectangle{

    id: mainRectangle
    visible: true
    width: 800
    height: 480

    function startScreenSaver()
    {
        loaderScreenSaver.setSource("screensaver.qml")
    }

    Connections{
            target: screensaverhelper
            onScreensavertimeout: mainRectangle.startScreenSaver()
    }


    MessageDialog {
        id: bluetoothPairMessage
        title: "Bluetooth"
        icon: StandardIcon.Question
        text: "Do You want pair with Bluetooth device?"
        standardButtons: StandardButton.Yes | StandardButton.No | StandardButton.Apply
        onYes: mainWindow.pairAndTrustWithBluetoothDevice();
        onApply: mainWindow.pairWithBluetoothDevice();
        onNo: mainWindow.cancelPairWithBluetoothDevice();

    }

    Loader {
        anchors.fill:parent
        source:"screensavermanager.qml";
    }

    ToolBar
    {
        id: toolBar
        anchors.topMargin: 0
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        font
        {
            family: "Comic Sans MS"
            pixelSize: 20
        }
        MessageDialog {
            id:shutdownMessage
            title: "Shutdown"
            icon: StandardIcon.Question
            text: "Are You sure to Power Off device?"
            standardButtons: StandardButton.Yes | StandardButton.No
            onYes: mainWindow.shutdownButton_OnClicked();
        }


        GridLayout
        {
            id: gridLayout
            height: 20
            anchors.right: parent.right
            anchors.rightMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            rows: 1
            columns: 3
            anchors.verticalCenter: parent.verticalCenter

            ToolButton {
                text: qsTr("Menu")
                onClicked: menu.open()

            }

            Menu {
                id: menu

                MenuItem {
                    text: "Mass Storage"
                    onClicked: {
                        loaderConfigWindow.setSource("massStorage.qml")
                    }
                }
                MenuSeparator { }
                MenuItem {
                    text: "Power Off"
                    onClicked: {
                        shutdownMessage.visible=true
                    }
                }

            }

            Text
            {
                id: tClockDate
                verticalAlignment: Text.AlignVCenter
                anchors.right:parent.right
                font
                {
                    family: "Comic Sans MS"
                    pixelSize: 20
                }
            }
         }

        Timer
        {
            interval: 1000
            running: true
            repeat: true
            onTriggered:
            {
                var date = new Date()
                var dateText = date.toLocaleDateString(Qt.locale("en_US"), "dddd, d MMM yyyy")
                var timeText = date.toLocaleTimeString(Qt.locale("en_US"), "hh:mm:ss")
                tClockDate.text = dateText + "   " + timeText
            }
        }
    }



    Loader {
        id: loaderConfigWindow
        anchors.fill: parent
        active: true
        asynchronous: true
    }

    Loader {
        id: loaderScreenSaver
        width: parent.width
        height: parent.height
        active: true
    }

    BusyIndicator
    {
        id: busyIndication
        anchors.centerIn: mainRectangle
        running: loaderConfigWindow.status == Loader.Loading
    }

    BusyIndicator
    {
        id: busyIndication1
        anchors.centerIn: mainRectangle
        running: true
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
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 120
                Layout.preferredWidth: 160
                background: Rectangle {color: "transparent"}

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
                Layout.preferredWidth: 160
                background: Rectangle {color: "transparent"}

                Image {
                    id: gmplayerImage
                    x: 37
                    y: 0
                    width: 116
                    height: 97
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/gmplayer.png"
                }
                Text {
                    id: gmplayerText
                    x: 81
                    y: 94
                    width: 50
                    height: 26
                    text: qsTr("Video")
                    font.letterSpacing: 1
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 17
                }

                onClicked:
                {
                    mainWindow.startVideoApplication()
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 120
                Layout.preferredWidth: 160
                background: Rectangle {color: "transparent"}
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
                Layout.preferredWidth: 160
                background: Rectangle {color: "transparent"}

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
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                background: Rectangle {color: "transparent"}
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
                background: Rectangle {color: "transparent"}
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
                background: Rectangle {color: "transparent"}
                Image {
                    id: dlnaImage
                    x: 37
                    y: 0
                    width: 88
                    height: 74
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/multimedia.png"
                }
                Text {
                    id: dlnaText
                    x: 81
                    y: 74
                    width: 50
                    height: 26
                    text: qsTr("Multimedia")
                    font.letterSpacing: 1
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    loaderConfigWindow.setSource("multimediaConfig.qml")
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                background: Rectangle {color: "transparent"}
                Image {
                    id: alarmImage
                    y: 0
                    width: 125
                    height: 85
                    anchors.horizontalCenterOffset: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    fillMode: Image.Stretch
                    source: "icons/alarm.png"
                }
                Text {
                    id: alarmText
                    x: 81
                    y: 74
                    width: 50
                    height: 26
                    text: qsTr("Alarm")
                    font.letterSpacing: 1
                    anchors.horizontalCenterOffset: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font.pointSize: 15
                }
                onClicked:
                {
                    loaderConfigWindow.setSource("alarmConfig.qml")
                }
            }

            ToolButton {
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredHeight: 80
                Layout.preferredWidth: 110
                background: Rectangle {color: "transparent"}

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
                background: Rectangle {color: "transparent"}
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

    Component.onCompleted:
    {
        busyIndication1.running=false
        mainWindow.getPairBluetoothMessage(bluetoothPairMessage)
    }
}
