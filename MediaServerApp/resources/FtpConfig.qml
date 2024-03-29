import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1

import FtpConfigLib 1.0

Dialog
{
    id: ftpConfigDialog
    visible: true
    width: parent.width
    height: parent.height - 40
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    FtpConfigView
    {
        id: ftpConfig
    }

    Loader {
        anchors.fill:parent
        source:"ScreenSaverManager.qml";
    }

    MessageDialog {
        id: fileErrorMessage
        title: "Warning"
        icon: StandardIcon.Warning
        text: "FTP confg file doesn't exist!"
        standardButtons: StandardButton.Close
        onButtonClicked: ftpConfigDialog.close()
    }

    FileDialog {
        id: fileDialog1
        selectFolder: true
        width: parent.width
        height: parent.height
        onAccepted:
        {
            ftpConfig.bFileDialog1_onAccepted(fileDialog1.folder)
            ftpConfigDialog.visible=true
        }
        onRejected:
        {
            ftpConfigDialog.visible=true
        }
    }

    FileDialog {
        id: fileDialog2
        width: parent.width
        height: parent.height
        selectFolder: true
        onAccepted:
        {
            ftpConfig.bFileDialog2_onAccepted(fileDialog2.folder)
            ftpConfigDialog.visible=true
        }
        onRejected:
        {
            ftpConfigDialog.visible=true
        }
    }


    RowLayout {
        id: rowLayout1
        anchors.fill: parent
        anchors.topMargin: 20

        GroupBox {
            id: groupBox1
            width: 412
            Layout.preferredHeight: 320
            Layout.preferredWidth: 400
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            title: qsTr("Edit User")

            GridLayout {
                id: gridLayout
                x: -12
                y: -7
                width: 393
                height: 287
                rows: 3
                columns: 3

                Text {
                    id: text1
                    text: qsTr("Users")
                    rightPadding: 0
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    font.pixelSize: 18
                }

                ComboBox {
                    id: userComboBox
                    Layout.preferredWidth: 200
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.columnSpan: 2
                    padding: 5
                    onDisplayTextChanged:
                    {
                        ftpConfig.cbUser_onDisplayTextChanged(userComboBox.currentText);
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
                    text: qsTr("/home/ftp")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    font.pixelSize: 18
                    readOnly: true
                }

                Button {
                    id: bOpenCatalog1
                    width: 87
                    text: "Open"
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 60
                    onClicked:
                    {
                        fileDialog1.open()
                        ftpConfigDialog.visible=false
                    }
                }

                Button {
                    id: removeUserButton
                    text: qsTr("Remove")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    onClicked:
                    {
                        ftpConfig.bRemoveUser_onClick(userComboBox.currentText);
                    }
                }

                Button {
                    id: updateUserButton
                    text: qsTr("Update")
                    Layout.columnSpan: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked:
                    {
                        ftpConfig.bUpdateUser_onClick(userComboBox.currentText,catalogTextField1.text);
                    }
                }
            }
        }

        GroupBox {
            id: groupBox2
            x: 424
            y: 35
            width: 354
            height: 334
            Layout.preferredWidth: 353
            Layout.preferredHeight: 320
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            title: qsTr("Add User")

            GridLayout {
                id: gridLayout1
                width: 327
                height: 282
                columns: 3

                Text {
                    id: userNameText
                    text: qsTr("User")
                    font.pixelSize: 18
                }

                TextField {
                    id: newUserNameTextField
                    width: 80
                    height: 20
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.columnSpan: 2
                    font.pixelSize: 18
                }

                Text {
                    id: passwordText
                    text: qsTr("Password")
                    font.pixelSize: 18
                }

                TextField {
                    id: passwordTextField
                    width: 80
                    height: 20
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.columnSpan: 2
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
                    text: qsTr("/home/ftp")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 134
                    font.pixelSize: 18
                    readOnly: true
                }

                Button {
                    id: bOpenCatalog2
                    width: 87
                    text: "Open"
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 60
                    onClicked:
                    {
                        fileDialog2.open()
                        ftpConfigDialog.visible=false
                    }
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

    RowLayout
    {
        id: buttonsRowLayout
        anchors.bottomMargin: 15
        anchors.rightMargin: 15

        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Button
        {
            id:saveButton
            height: 40
            text: "Save"
            onClicked:
            {
                ftpConfig.bSave_onClicked()
            }
            onPressed: { busyFtpConfig.running=true }
            onReleased:{ busyFtpConfig.running=false }
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


    BusyIndicator
    {
        id: busyFtpConfig
        anchors.centerIn: parent
        height: 100
        width: 100
        running: false
    }

    InputPanel
    {
        id: inputPanel
        y: ftpConfigDialog.height+40
        width: ftpConfigDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: ftpConfigDialog.parent.height - inputPanel.height
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
        if (ftpConfig.fileValid)
        {
        ftpConfig.setPathTextField1(catalogTextField1)
        ftpConfig.setPathTextField2(catalogTextField2)
        ftpConfig.setUsersComboBox(userComboBox)
        ftpConfig.checkService(saveButton)
        }
        else
        {
            fileErrorMessage.setVisible(true)
        }
    }
}
