import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import FtpConfigLib 1.0

Dialog
{
    id: ftpConfigDialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    FtpConfig
    {
        id: ftpConfig
    }

    RowLayout
    {
        id: rowLayout
        anchors.bottomMargin: 8
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Button
        {
            width: 160
            height: 40
            text: "Save"
            onClicked:
            {
                //save action
            }
        }

        Button
        {
            text: "Close"
            width: 160
            height: 40
            onClicked:
            {
                ftpConfigDialog.close()
            }
        }
    }

    GridLayout {
        id: gridLayout
        x: 17
        y: 8
        width: 326
        height: 93
        rows: 2
        columns: 2

        Text {
            id: text1
            text: qsTr("Users")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pixelSize: 18
        }

        ComboBox {
            id: userComboBox
            Layout.preferredWidth: 210
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            onDisplayTextChanged:
            {
                ftpConfig.cbUser_onDisplayTextChanged(userComboBox.currentText);
            }
        }

    }

    GridLayout {
        id: gridLayout1
        x: 409
        y: 8
        width: 367
        height: 368
        columns: 2

        Text {
            id: userNameText
            text: qsTr("User")
            font.pixelSize: 18
        }

        TextField {
            id: userNameTextField
            width: 80
            height: 20
            text: qsTr("Text Edit")
            font.pixelSize: 18
        }

        Text {
            id: passwordText
            text: qsTr("password")
            font.pixelSize: 18
        }

        TextField {
            id: passwordTextField
            width: 80
            height: 20
            text: qsTr("Text Edit")
            font.pixelSize: 18
            echoMode: TextInput.PasswordEchoOnEdit
        }

        Text {
            id: catalogText
            text: qsTr("Catalog")
            font.pixelSize: 18
        }

        TextField {
            id: catalogTextField
            width: 80
            height: 20
            text: qsTr("Text Edit")
            font.pixelSize: 18
        }

        Button {
            id: removeUserButton
            text: qsTr("Remove User")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked:
            {
                //remove user action
            }


        }

        Button {
            id: newUserButton
            text: qsTr("Add/Update User")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            onClicked:
            {
                //add user action
            }
        }

    }

    InputPanel
    {
        id: inputPanel
        z: 99
        x: 0
        y: ftpConfigDialog.height
        width: ftpConfigDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: ftpConfigDialog.height - inputPanel.height
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
        ftpConfig.setUsersComboBox(userComboBox)
    }

}
