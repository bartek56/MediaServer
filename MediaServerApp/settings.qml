import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1

import SettingsLib 1.0

Dialog
{
    id: settingsDialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    Settings
    {
        id: settings
    }
    BusyIndicator
    {
        id: busyIndication
        anchors.centerIn: parent
    }

    TabBar
    {
        id: tabBar
        width: parent.width
        TabButton {
            text: qsTr("Wi-fi")
        }
    }

    StackLayout
    {
        id: stackLayout
        width: parent.width
        currentIndex: tabBar.currentIndex

        Item
        {
            id: wifiSettingsTag

            GridLayout {
                id: gridLayout
                x: 38
                y: 51
                width: 352
                height: 313
                rows: 5
                columns: 2

                Text {
                    id: networkText
                    text: qsTr("Network")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    Layout.columnSpan: 2
                    font.pixelSize: 16
                }

                ComboBox {
                    id: networksComboBox
                    Layout.preferredWidth: 250
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.columnSpan: 2
                }

                Text {
                    id: passwordText
                    text: qsTr("Password")
                    font.pixelSize: 16
                }

                TextField {
                    id: passwordTextField
                    width: 80
                    height: 20
                    text: qsTr("password")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 16
                }

                Button {
                    id: button
                    text: qsTr("Connect")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.columnSpan: 2
                    onClicked:
                    {
                        settings.connect(networksComboBox.currentText,passwordTextField.text)
                        passwordTextField.clear()
                    }
                }
            }

            GridLayout {
                id: gridLayout1
                x: 414
                y: 51
                width: 352
                height: 313
                rows: 2
                columns: 1

                Text {
                    id: infoText
                    text: qsTr("Info")
                    font.letterSpacing: 4
                    lineHeight: 1
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    font.pixelSize: 21
                }

                Text {
                    id: infoText2
                    text: qsTr("")
                    Layout.preferredHeight: 280
                    Layout.preferredWidth: 370
                    wrapMode: Text.WordWrap
                    font.family: "Tahoma"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 12
                }
            }

        }

    }

    InputPanel
    {
        id: inputPanel
        z: 99
        x: 0
        y: settingsDialog.height
        width: settingsDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: settingsDialog.height - inputPanel.height
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


    RowLayout {
        id: rowLayout
        anchors.bottomMargin: 8
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Button
        {
            width: 160
            height: 40
            text: "Refresh"
            onClicked:
            {
                settings.updateStatus(infoText2)
            }
        }

        Button
        {
            text: "Close"
            width: 160
            height: 40
            onClicked:
            {
                settingsDialog.close()
            }
        }
    }

    Component.onCompleted:
    {
        settings.updateStatus(infoText2)
        settings.searchNetworks(networksComboBox)

        busyIndication.running = false
    }


}
