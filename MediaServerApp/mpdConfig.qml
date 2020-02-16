import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import MpdConfigLib 1.0

Dialog
{
    id: mpdConfigDialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    MpdConfig
    {
        id: mpdConfig
    }

    Loader {
        anchors.fill:parent
        source:"screensaver.qml";
    }

    FileDialog {
        id: musicFileDialog
        width: parent.width
        height: parent.height
        folder: shortcuts.home
        //folder: shortcuts.mnt
        selectFolder: true
        onAccepted:
        {
            mpdConfig.bMusicFileDialog_onAccepted(musicFileDialog.folder,musicPathEditText)
            mpdConfigDialog.visible=true
        }
        onRejected:
        {
            mpdConfigDialog.visible=true
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
            Layout.preferredHeight: 197
            Layout.preferredWidth: 400
            title: qsTr("Music Directory")
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
                    id: musicText
                    text: qsTr("Music")
                    font.pixelSize: 16
                }

                TextField {
                    id: musicPathEditText
                    text: qsTr("/home/ftp")
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
                        musicFileDialog.open()
                        mpdConfigDialog.visible=false
                    }
                }
            }
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
                    mpdConfig.saveConfigs();
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
                    mpdConfigDialog.close()
                }
            }
        }
    }

    InputPanel
    {
        id: inputPanel
        z: 99
        x: 0
        y: mpdConfigDialog.height
        width: mpdConfigDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: mpdConfigDialog.height - inputPanel.height
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
        mpdConfig.loadConfigs(musicPathEditText);
        mpdConfig.checkService(saveButton);
    }
}


