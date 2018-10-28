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
    BusyIndicator
    {
        id: busyIndication
        anchors.centerIn: parent
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
                ftpConfig.bSave_onClicked()
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

    RowLayout {
        id: rowLayout1
        x: 8
        y: 0
        width: 792
        height: 369

        GroupBox {
            id: groupBox1
            Layout.preferredHeight: 320
            Layout.preferredWidth: 400
            title: qsTr("Edit User")

            GridLayout {
                id: gridLayout
                x: -12
                y: -7
                width: 388
                height: 287
                rows: 3
                columns: 2

                Text {
                    id: text1
                    text: qsTr("Users")
                    rightPadding: 0
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    font.pixelSize: 18
                }

                ComboBox {
                    id: userComboBox
                    x: 180
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    padding: 5
                    Layout.preferredWidth: 210
                    onDisplayTextChanged:
                    {
                        busyIndication.running = true
                        ftpConfig.cbUser_onDisplayTextChanged(userComboBox.currentText);
                        busyIndication.running = false
                    }
                }

                Text {
                    id: text2
                    text: qsTr("Catalog")
                    font.pixelSize: 18
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                }

                TextField {
                    id: catalogTextField1
                    x: 190
                    width: 80
                    height: 20
                    text: qsTr("Text Edit")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    font.pixelSize: 18
                    onEditingFinished:
                    {

                    }
                }

                Button {
                    id: removeUserButton
                    text: qsTr("Remove")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked:
                    {
                        busyIndication.running = true
                        //remove user action
                        busyIndication.running = false
                    }
                }

                Button {
                    id: updateUserButton
                    text: qsTr("Update")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked:
                    {
                        busyIndication.running = true
                        //remove user action
                        busyIndication.running = false
                    }
                }
            }
        }

        GroupBox {
            id: groupBox2
            x: 441
            y: 35
            Layout.preferredHeight: 350
            title: qsTr("Add User")

            GridLayout {
                id: gridLayout1
                width: 327
                height: 282
                columns: 2

                Text {
                    id: userNameText
                    text: qsTr("User")
                    font.pixelSize: 18
                }

                TextField {
                    id: newUserNameTextField
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
                    id: catalogTextField2
                    width: 80
                    height: 20
                    text: qsTr("Text Edit")
                    font.pixelSize: 18
                }

                Button {
                    id: newUserButton
                    text: qsTr("Add User")
                    Layout.columnSpan: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked:
                    {
                        ftpConfig.bAddUser_onClicked(
                                    newUserNameTextField.getText(0,newUserNameTextField.length),
                                    passwordTextField.getText(0,passwordTextField.length),
                                    catalogTextField2.getText(0,catalogTextField2.length));
                        newUserNameTextField.text=""
                        passwordTextField.text=""
                        catalogTextField2.text=""
                    }
                }

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
        ftpConfig.setPathTextField(catalogTextField1)
        ftpConfig.setUsersComboBox(userComboBox)
        busyIndication.running = false
    }
}
