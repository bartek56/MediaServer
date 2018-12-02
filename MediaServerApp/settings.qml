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
    Loader {
        anchors.fill:parent
        source:"screensaver.qml";
    }

    FileDialog {
        id: screenSaverFileDialog
        folder: shortcuts.home
        selectFolder: true
        onAccepted:
        {
            settings.bScreenSaverFileDialog_onAccepted(screenSaverFileDialog.folder, pathScreenSaverTextField)
            settingsDialog.visible=true
        }
        onRejected:
        {
            settingsDialog.visible=true
        }
    }

    TabBar
    {
        id: tabBar
        width: parent.width

        TabButton {
            text: qsTr("Status")
        }

        TabButton {
            text: qsTr("Wi-fi")
        }

        TabButton {
            text: qsTr("External Devices")
        }
        TabButton {
            text: qsTr("Screen Saver")
        }

    }

    StackLayout
    {
        id: stackLayout
        width: parent.width
        currentIndex: tabBar.currentIndex

        Item
        {
            id: statusTag

            GridLayout {
                x: 38
                y: 51
                width: 352
                height: 313
                rows: 5
                columns: 2

            }

            GridLayout {
                x: 414
                y: 51
                width: 352
                height: 313
                rows: 2
                columns: 1

                Text {
                    text: qsTr("Network Status")
                    font.letterSpacing: 4
                    lineHeight: 1
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    font.pixelSize: 21
                }

                Text {
                    id: networkInfoText
                    Layout.preferredHeight: 210
                    Layout.preferredWidth: 370
                    wrapMode: Text.WordWrap
                    font.family: "Tahoma"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 12
                    function set() {
                        settings.updateNetworkStatus(networkInfoText)
                    }
                }

                Timer {
                    id: timerNetworkStatus
                    interval: 2000
                    repeat: true
                    running: true
                    triggeredOnStart: true
                    onTriggered: networkInfoText.set()
                }
            }
        }

        Item
        {
            id: wifiSettingsTag

            GridLayout {
                x: 38
                y: 51
                width: 352
                height: 313
                rows: 5
                columns: 2

                Text {
                    id: networkText
                    text: qsTr("SSID")
                    bottomPadding: 9
                    verticalAlignment: Text.AlignTop
                    Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                    horizontalAlignment: Text.AlignLeft
                    Layout.columnSpan: 1
                    font.pixelSize: 16
                }

                ComboBox {
                    id: networksComboBox
                    Layout.preferredWidth: 200
                    Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
                    onDisplayTextChanged:
                    {
                        settings.cbNetworks_onDisplayTextChanged(networksComboBox.currentText,wifiInfoText);
                    }
                }

                Text {
                    id: wifiInfoText
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.columnSpan: 2
                    font.pixelSize: 12

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
                    text: qsTr("")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 16
                }

                Button {
                    id: scanNetworkButton
                    text: qsTr("Scan Network")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked:
                    {
                        busyIndication.running = true
                        settings.searchNetworks(networksComboBox)
                        busyIndication.running = false
                    }
                }

                Button {
                    id: connectButton
                    text: qsTr("Connect")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked:
                    {
                        settings.connect(networksComboBox.currentText,passwordTextField.text)
                        passwordTextField.clear()
                    }
                }
            }

            GridLayout {
                x: 414
                y: 51
                width: 352
                height: 313
                rows: 2
                columns: 1

                Text {
                    text: qsTr("Info")
                    font.letterSpacing: 4
                    lineHeight: 1
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    font.pixelSize: 21
                }

                Text {
                    id: infoWifiText
                    Layout.preferredHeight: 210
                    Layout.preferredWidth: 370
                    wrapMode: Text.WordWrap
                    font.family: "Tahoma"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 12
                    function set() {
                        settings.updateWifiStatus(infoWifiText)
                    }
                }
                Switch {
                    id: wifiOnSwitch
                    text: qsTr("Power on")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    function updatestate()
                    {
                        if (checked === true)
                        {
                            connectButton.enabled=true
                            scanNetworkButton.enabled=true
                            networksComboBox.enabled=true
                        }
                        else
                        {
                            networksComboBox.enabled=false
                            connectButton.enabled=false
                            scanNetworkButton.enabled=false
                        }
                    }
                    onCheckedChanged:
                    {
                        settings.sWifiOn_OnCheckedChanged(wifiOnSwitch.checked)
                        updatestate()
                    }
                }

                Timer {
                    id: timerWifiStatus
                    interval: 2000
                    repeat: true
                    running: true
                    triggeredOnStart: true
                    onTriggered: infoWifiText.set()
                }
            }
        }

        Item
        {
            id: externalDevicesSettingsTag

            RowLayout {

                anchors.rightMargin: 20
                anchors.leftMargin: 20
                anchors.topMargin: 60
                anchors.bottomMargin: -374
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
                        text: qsTr("Device")
                        font.pixelSize: 16
                    }

                    ComboBox {
                        id: devicesComboBox
                        Layout.preferredWidth: 200
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onDisplayTextChanged:
                        {
                            settings.cbDevices_onDisplayTextChanged(devicesComboBox.currentText, deviceSizeText, nameDeviceText,mountPointText);
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
                        text: qsTr("Device")
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
                        text: qsTr("Device")
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
                        text: qsTr("Device")
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
                            settings.bMount_onClicked(mountPointText.text, nameDeviceText.text, devicesComboBox.currentText,automountCheckBox.checked)
                            settings.cbDevices_onDisplayTextChanged(devicesComboBox.currentText, deviceSizeText, nameDeviceText,mountPointText)
                            setText()
                        }
                    }
                }

                GridLayout {
                    width: 100
                    height: 100
                }
            }
        }

        Item
        {
            id: screensaverSettingsTag

            RowLayout {

                anchors.rightMargin: 20
                anchors.leftMargin: 20
                anchors.topMargin: 60
                anchors.bottomMargin: -374
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top

                GridLayout {
                    width: 100
                    height: 100
                    rowSpacing: 30
                    rows: 4
                    Layout.preferredWidth: 300
                    columns: 3
                    Layout.alignment: Qt.AlignLeft | Qt.AlignTop


                    Text {
                        text: qsTr("Start Time[min]")
                        font.pixelSize: 16
                    }

                    SpinBox {
                        id: startTimeSpinBox
                        width: 138
                        from: 1
                        to: 15
                        Layout.columnSpan: 2
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        font.pointSize: 11
                    }

                    Text {
                        text: qsTr("Timeout [s]")
                        font.pixelSize: 16
                    }

                    SpinBox {
                        id: timeOutSpinBox
                        width: 138
                        from: 1
                        to: 10
                        Layout.columnSpan: 2
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        font.pointSize: 11
                    }

                    CheckBox {
                        id: randomCheckBox
                        text: qsTr("Random")
                        Layout.columnSpan: 3
                        checkable: true
                    }

                    Text {
                        text: qsTr("Catalog")
                        font.pixelSize: 16
                    }

                    TextField {
                        id: pathScreenSaverTextField
                        text: qsTr("/home/pictures/")
                        readOnly: true
                        Layout.preferredWidth: 190
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    }

                    Button {
                        id: button
                        text: qsTr("Open")
                        Layout.preferredWidth: 60
                        onClicked:
                        {
                            screenSaverFileDialog.open()
                            settingsDialog.visible=false
                        }
                    }
                }

                GridLayout {
                    width: 100
                    height: 100
                }
            }

            Button
            {
                id:saveScreenSaverButton
                x: 559
                y: 380
                width: 100
                height: 40
                text: "save"
                Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                Layout.columnSpan: 2
                onClicked:
                {
                    settings.bSaveScreenSaver_onClicked(timeOutSpinBox.value,pathScreenSaverTextField.text,startTimeSpinBox.value,randomCheckBox.checked)
                }
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
                settingsDialog.close()
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

    Component.onCompleted:
    {
        settings.checkWifi(wifiOnSwitch)
        wifiOnSwitch.updatestate()
        settings.loadWifiConfigFile()
        settings.loadExternalDevices(devicesComboBox)
        settings.loadScreenSaverConfigurations(startTimeSpinBox,pathScreenSaverTextField,timeOutSpinBox,randomCheckBox)
        busyIndication.running = false
    }
}

