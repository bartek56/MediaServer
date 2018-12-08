import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import DlnaConfigLib 1.0

Dialog
{
    id: dlnaConfigDialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    DlnaConfig
    {
        id: dlnaConfig
    }

    Loader {
        anchors.fill:parent
        source:"screensaver.qml";
    }

    FileDialog {
        id: videoFileDialog
        folder: shortcuts.home
        //folder: shortcuts.mnt
        selectFolder: true
        onAccepted:
        {
            dlnaConfig.bVideoFileDialog_onAccepted(videoFileDialog.folder,videoPathEditText)
            dlnaConfigDialog.visible=true
        }
        onRejected:
        {
            dlnaConfigDialog.visible=true
        }
    }

    FileDialog {
        id: audioFileDialog
        folder: shortcuts.home
        //folder: shortcuts.mnt
        selectFolder: true
        onAccepted:
        {
            dlnaConfig.bAudioFileDialog_onAccepted(audioFileDialog.folder,audioPathEditText)
            dlnaConfigDialog.visible=true
        }
        onRejected:
        {
            dlnaConfigDialog.visible=true
        }
    }

    FileDialog {
        id: picturesFileDialog
        folder: shortcuts.home
        //folder: shortcuts.mnt
        selectFolder: true
        onAccepted:
        {
            dlnaConfig.bPicturesFileDialog_onAccepted(picturesFileDialog.folder,picturePathEditText)
            dlnaConfigDialog.visible=true
        }
        onRejected:
        {
            dlnaConfigDialog.visible=true
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
                        dlnaConfigDialog.visible=false
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
                        dlnaConfigDialog.visible=false
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
                        dlnaConfigDialog.visible=false
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
                        dlnaConfig.tfPort_onEditingFinished(portEditText.text);
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
                        dlnaConfig.tfName_onEditingFinished(nameEditText.text);
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
                    dlnaConfig.saveConfigs();
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
                    dlnaConfigDialog.close()
                }
            }
        }
    }

    InputPanel
    {
        id: inputPanel
        z: 99
        x: 0
        y: dlnaConfigDialog.height
        width: dlnaConfigDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: dlnaConfigDialog.height - inputPanel.height
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
        dlnaConfig.openConfigFile();
        dlnaConfig.loadMediaDirectoryConfigs(videoPathEditText,audioPathEditText,picturePathEditText);
        dlnaConfig.loadSettigs(portEditText,nameEditText);
        dlnaConfig.checkService(saveButton)
    }

}


