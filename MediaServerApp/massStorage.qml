import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1
import MassStorageLib 1.0

Dialog
{
    id: massStorageDialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true
    MassStorage
    {
        id: massStorage
    }

    /*Loader {
        anchors.fill:parent
        source:"screensaver.qml";
    }
*/

    RowLayout {
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 60
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        GridLayout {
            width: 100
            height: 100
            rows: 7
            Layout.preferredWidth: 300
            columns: 2
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Text {
                id: deviceText
                font.pixelSize: 16
            }

            ComboBox {
                id: devicesComboBox
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                onDisplayTextChanged:
                {
                            massStorage.cbDevices_onDisplayTextChanged(devicesComboBox.currentText, deviceSizeText, nameDeviceText,mountPointText,typeText);
                            mountButton.setText()
                }
            }

            Text {
                id: deviceSize
                text: qsTr("Size:")
                font.pixelSize: 16
            }

            Text {
                id: deviceSizeText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 16
            }

            Text {
                id: nameDevice
                text: qsTr("Name")
                font.pixelSize: 16
            }

            Text {
                id: nameDeviceText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 16
            }

            Text {
                id: mountPoint
                text: qsTr("MountPoint")
                font.pixelSize: 16
            }

            Text {
                id: mountPointText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 16
            }

            Text {
                id: type
                text: qsTr("File Type")
                font.pixelSize: 16
            }

            Text {
                id: typeText
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pixelSize: 16
            }

            CheckBox {
                id: automountCheckBox
                text: qsTr("automount")
                font.pointSize: 10
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignRight | Qt.AlignTop
            }

            Button
            {
                id:mountButton
                width: 160
                height: 40
                enabled: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                Layout.columnSpan: 2
                function setText()
                {
                    if(mountPointText.text.length>2)
                    {
                        text="umount"
                    }
                    else
                    {
                        text="mount"
                    }
                }
                onClicked:
                {
                    massStorage.bMount_onClicked(mountPointText.text, nameDeviceText.text, devicesComboBox.currentText,automountCheckBox.checked, typeText.text)
                    massStorage.cbDevices_onDisplayTextChanged(devicesComboBox.currentText, deviceSizeText, nameDeviceText,mountPointText,typeText)
                    setText()
                }
            }
        }
    RowLayout {
        id: rowLayout
        y: 376
        anchors.bottomMargin: 20
        anchors.rightMargin: 20
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Button
        {
            text: "Close"
            height: 40
            onClicked:
            {
                massStorageDialog.close()
            }
        }
    }

        GridLayout {
            width: 100
            height: 100
        }
    }

    Component.onCompleted: {
        massStorage.loadExternalDevices(devicesComboBox,mountButton)
    }
}
