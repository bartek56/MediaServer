import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import MultimediaConfigLib 1.0

Dialog
{
    id: multimediaConfigDialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    MultimediaConfig
    {
        id: multimediaConfig
    }

    Loader {
        id: loader
        anchors.fill: parent
        active: false
        asynchronous: true
    }


    BusyIndicator
    {
        id: busyIndication
        anchors.centerIn: mainRectangle
        running: loader.status == Loader.Loading
    }

    Loader {
        anchors.fill:parent
        source:"screensaver.qml";
    }

    FileDialog {
        id: videoFileDialog
        folder: shortcuts.home
        //folder: shortcuts.mnt
        width: parent.width
        height: parent.height
        selectFolder: true
        onAccepted:
        {
            multimediaConfig.bVideoFileDialog_onAccepted(videoFileDialog.folder,videoPathEditText)
            multimediaConfigDialog.visible=true
        }
        onRejected:
        {
            multimediaConfigDialog.visible=true
        }
    }

    FileDialog {
        id: audioFileDialog
        folder: shortcuts.home
        width: parent.width
        height: parent.height
        selectFolder: true
        onAccepted:
        {
            multimediaConfig.bAudioFileDialog_onAccepted(audioFileDialog.folder,audioPathEditText)
            multimediaConfigDialog.visible=true
        }
        onRejected:
        {
            multimediaConfigDialog.visible=true
        }
    }

    FileDialog {
        id: picturesFileDialog
        folder: shortcuts.home
        width: parent.width
        height: parent.height
        selectFolder: true
        onAccepted:
        {
            multimediaConfig.bPicturesFileDialog_onAccepted(picturesFileDialog.folder,picturePathEditText)
            multimediaConfigDialog.visible=true
        }
        onRejected:
        {
            multimediaConfigDialog.visible=true
        }
    }

    RowLayout {
        spacing: 80
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        GroupBox {
            id: groupBox
            width: 390
            font.pointSize: 16
            Layout.preferredHeight: 250
            Layout.preferredWidth: 400
            title: qsTr("Media Directory")
            topPadding: 45
            leftPadding: 50
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            GridLayout {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                rows: 7

                columns: 3
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                Text {
                    id: audioText
                    text: qsTr("Audio")
                    font.pixelSize: 16
                }

                TextField {
                    id: audioPathEditText
                    text: qsTr("/home/ftp")
                    readOnly: true
                    font.pixelSize: 16
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                }

                Button {
                    id: audioPathButton
                    text: qsTr("Open")
                    font.pointSize: 11
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 60
                    onClicked:
                    {
                        audioFileDialog.open()
                        multimediaConfigDialog.visible=false
                    }
                }

                Text {
                    id: videoText
                    text: qsTr("Video")
                    font.pixelSize: 16
                }

                TextField {
                    id: videoPathEditText
                    text: qsTr("/home/ftp")
                    readOnly: true
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    font.pixelSize: 16
                }

                Button {
                    id: videoPathButton
                    text: qsTr("Open")
                    font.pointSize: 11
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 60
                    onClicked:
                    {
                        videoFileDialog.open()
                        multimediaConfigDialog.visible=false
                    }
                }

                Text {
                    id: pictureText
                    text: qsTr("Picture")
                    font.pixelSize: 16
                }

                TextField {
                    id: picturePathEditText
                    text: qsTr("/home/ftp")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    readOnly: true
                    font.pixelSize: 16
                }

                Button {
                    id: picturePathButton
                    text: qsTr("Open")
                    font.pointSize: 11
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 60
                    onClicked:
                    {
                        picturesFileDialog.open()
                        multimediaConfigDialog.visible=false
                    }
                }
            }
        }

        GroupBox {
            id: groupBox1
            width: 390
            font.pointSize: 16
            GridLayout {
                anchors.left: parent.left
                rows: 2
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                columns: 2
                Text {
                    id: portText
                    text: qsTr("Port")
                    font.pixelSize: 16
                }

                TextField {
                    id: portEditText
                    text: qsTr("8200")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 60
                    font.pixelSize: 16
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onEditingFinished:
                    {
                        multimediaConfig.tfPort_onEditingFinished(portEditText.text);
                    }
                }

                Text {
                    id: nameText
                    text: qsTr("Name")
                    font.pixelSize: 16
                }

                TextField {
                    id: nameEditText
                    text: qsTr("Media Server")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: 150
                    font.pixelSize: 16
                    onEditingFinished:
                    {
                        multimediaConfig.tfName_onEditingFinished(nameEditText.text);
                    }
                }
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                anchors.top: parent.top
            }
            title: qsTr("Settings")
            topPadding: 45
            Layout.preferredWidth: 250
            Layout.preferredHeight: 250
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            leftPadding: 50
        }


        RowLayout {
            id: rowLayout
            anchors.bottomMargin: 8
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            Button
            {
                id: saveButton
                width: 160
                height: 40
                text: "Save"
                onClicked:
                {
                    busyIndication.running=true
                    multimediaConfig.saveConfigs();
                    busyIndication.running=false
                }
            }

            Button
            {
                id: closeButton
                text: "Close"
                width: 160
                height: 40
                onClicked:
                {
                    multimediaConfigDialog.close()
                }
            }
        }
    }

    InputPanel
    {
        id: inputPanel
        z: 99
        x: 0
        y: multimediaConfigDialog.height
        width: multimediaConfigDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: multimediaConfigDialog.height - inputPanel.height
            }
        }

        transitions: Transition
        {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation
            {
                NumberAnimation
                {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    Component.onCompleted:
    {
        multimediaConfig.openConfigFile();
        multimediaConfig.loadMediaDirectoryConfigs(videoPathEditText,audioPathEditText,picturePathEditText);
        multimediaConfig.loadSettings(portEditText,nameEditText);
        multimediaConfig.checkService(saveButton)
    }
}


