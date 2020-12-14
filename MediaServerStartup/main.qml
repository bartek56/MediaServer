import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import MainWindowLib 1.0
import SettingsLib 1.0

Rectangle
{
    id: dialog
    height: 480
    width: 800

    Settings
    {
        id: settings
    }

    MainWindow
    {
        id: mainWindow
    }

    StackLayout
    {
        id: layout

        Rectangle {
            id: helloRectangle
            visible: true
            width: 800
            height: 480

            Text {
                x: 233
                y: 76
                width: 335
                height: 96
                text: qsTr("Welcome")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 42
            }

            Text {
                x: 265
                y: 194
                width: 271
                height: 55
                text: qsTr("First Configuration")
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Button {
                x: 666
                y: 407
                text: qsTr("Next")
                onClicked:
                {
                    layout.currentIndex=1
                }
                onPressed: {busy.running=true}
                onReleased: {busy.running=false}
            }
        }


        Rectangle {
            id: rectangleRootPassword
            visible: true
            width: 800
            height: 480

            Text {
                x: 265
                y: 40
                width: 271
                height: 55
                text: qsTr("Password")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 42
            }

            GridLayout {
                x: 209
                y: 148
                width: 383
                height: 200
                rows: 2
                columns: 2

                Text {
                    text: qsTr("User")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    font.pixelSize: 30
                }
                TextField {
                    width: 80
                    height: 20
                    text: "root"
                    enabled: false
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    readOnly: true
                    font.pixelSize: 30
                }
                Text {
                    text: qsTr("Password")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    font.pixelSize: 30
                }

                TextField {
                    id: textRootPassword
                    width: 80
                    height: 20
                    text: qsTr("root")
                    horizontalAlignment: Text.AlignHCenter
                    Layout.fillWidth: true
                    font.pixelSize: 30
                }
            }

            Button {
                x: 45
                y: 407
                text: qsTr("Back")
                onClicked:
                {
                    layout.currentIndex=0
                }
            }

            Button {
                x: 666
                y: 407
                text: qsTr("Next")
                onClicked:
                {
                    layout.currentIndex=2
                }
                onPressed: {busy.running=true}
                onReleased: {busy.running=false}
            }
        }


        Rectangle
        {
            id: ipAddressConfig
            Text {
                id: element
                y: 30
                width: dialog.width
                height: 55
                text: qsTr("IP Address")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 45
            }

            GridLayout {
                x: 38
                y: 95
                width: 352
                height: 260
                columns: 2

                Text {
                    id: networkInterfaceText
                    text: qsTr("Interface")
                    verticalAlignment: Text.AlignVCenter
                    bottomPadding: 9
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 16
                }

                ComboBox {
                    id: networkInterfaceComboBox
                    Layout.preferredWidth: 200
                    model:["Wi-Fi", "Ethernet"]
                    onDisplayTextChanged:
                    {
                        settings.loadIpAddressConfiguration(networkInterfaceComboBox.currentIndex, dynamicIPRadioButton,
                                                            staticIPRadioButton,ipadressTextField,netmaskTextField,
                                                            gatewayTextField,dnsserverTextField);
                    }
                }

                Text {
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignTop
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.columnSpan: 2
                    font.pixelSize: 12

                }


                ColumnLayout {
                    id: columnLayout
                    width: 100
                    height: 100
                    Layout.columnSpan: 2

                    RadioButton {
                        id: dynamicIPRadioButton
                        text: qsTr("Dynamic IP [DHCP]")
                        Layout.columnSpan: 2
                        onClicked:
                        {
                            if(dynamicIPRadioButton.checked)
                            {
                                ipadressTextField.enabled=false
                                netmaskTextField.enabled=false
                                gatewayTextField.enabled=false
                                dnsserverTextField.enabled=false
                                settings.rbDynamicIP_onClicked()
                            }
                        }
                    }

                    RadioButton {
                        id: staticIPRadioButton
                        text: qsTr("Static IP")
                        Layout.columnSpan: 2
                        onClicked:
                        {
                            if(staticIPRadioButton.checked)
                            {
                                ipadressTextField.enabled=true
                                netmaskTextField.enabled=true
                                gatewayTextField.enabled=true
                                dnsserverTextField.enabled=true
                                settings.rbStaticIP_onClicked(ipadressTextField.text, netmaskTextField.text,
                                                              gatewayTextField.text, dnsserverTextField.text)
                            }
                        }
                    }
                }
            }

            GridLayout {
                x: 416
                y: 95
                width: 362
                height: 260
                rows: 2
                columns: 2

                Text {
                    text: qsTr("IP Address")
                    font.pixelSize: 16
                }

                TextField {
                    id: ipadressTextField
                    width: 80
                    height: 20
                    text: qsTr("192.168.1.155")
                    horizontalAlignment: Text.AlignHCenter
                    font.pixelSize: 16
                    onEditingFinished:
                    {
                        settings.tfIpAddress_onEditingFinished(ipadressTextField.text)
                    }

                }

                Text {
                    text: qsTr("NetMask")
                    font.pixelSize: 16
                }

                TextField {
                    id: netmaskTextField
                    width: 80
                    height: 20
                    text: qsTr("255.255.255.0")
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    onEditingFinished:
                    {
                        settings.tfNetMask_onEditingFinished(netmaskTextField.text)
                    }

                }

                Text {
                    text: qsTr("Gateway")
                    font.pixelSize: 16
                }

                TextField {
                    id: gatewayTextField
                    width: 80
                    height: 20
                    text: qsTr("192.168.1.1")
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    onEditingFinished:
                    {
                        settings.tfGateway_onEditingFinished(gatewayTextField.text)
                    }

                }

                Text {
                    text: qsTr("DNS Server")
                    font.pixelSize: 16
                }

                TextField {
                    id: dnsserverTextField
                    width: 80
                    height: 20
                    text: qsTr("192.168.1.1")
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                    onEditingFinished:
                    {
                        settings.tfDNSServer_onEditingFinished(dnsserverTextField.text)
                    }
                }
            }

            Button {
                x: 45
                y: 407
                text: qsTr("Back")
                onClicked:
                {
                    layout.currentIndex=1
                }
            }

            Button {
                x: 666
                y: 407
                text: qsTr("Next")
                onClicked:
                {
                    layout.currentIndex=3
                    settings.saveIpAddressConfiguration()
                }
                onPressed: {busy.running=true}
                onReleased: {busy.running=false}
            }

        }


        Rectangle
        {
            id:rectangleWifiConfig

            Text {
                y: 30
                width: dialog.width
                height: 55
                text: qsTr("Wifi Config")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 45
            }

            GridLayout {
                x: 37
                y: 84
                width: 352
                height: 280
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
                        settings.searchNetworks(networksComboBox)
                    }
                    onPressed: { busy.running=true }
                    onReleased:{ busy.running=false }
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
                    onPressed: { busy.running=true }
                    onReleased:{ busy.running=false }

                }
            }

            GridLayout {
                x: 414
                y: 80
                width: 352
                height: 289
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
                    onPressed: { busy.running=true }
                    onReleased:{ busy.running=false }

                }

                Timer {
                    id: timerWifiStatus
                    interval: 2000
                    repeat: true
                    running: true
                    triggeredOnStart: true
                    onTriggered: infoWifiText.set()
                }
                Timer {
                    id: timerNetworkStatus
                    interval: 3500
                    repeat: true
                    running: true
                    triggeredOnStart: true
                    onTriggered: mainWindow.checkNetwork(buttonExit, timerNetworkStatus)
                }
            }

            Button {
                id: backButton
                x: 45
                y: 407
                text: qsTr("Back")
                onClicked:
                {
                    layout.currentIndex=2
                }
            }

            Button {
                id: buttonExit
                x: 666
                y: 407
                enabled: false
                text: qsTr("Exit")
                onClicked:
                {
                    scanNetworkButton.enabled=false
                    connectButton.enabled=false
                    wifiOnSwitch.enabled=false

                    backButton.enabled=false
                    enabled=false
                    message.visible=true

                    mainWindow.savePassword(textRootPassword.text)
                    mainWindow.updateConfig()
                }
                onPressed: {lastBusy.running=true}
            }
        }
    }

    MessageDialog
    {
        id: message
        title: "Updating"
        visible: false
        icon:StandardIcon.Question
        text: "Please wait 3-5 minutes to configure system.\nSystem will restart automatically"
    }

    BusyIndicator
    {
        id: busy
        anchors.centerIn: parent
        height: 100
        width: 100
        running: false
    }

    BusyIndicator
    {
        id: lastBusy
        anchors.centerIn: parent
        height: 150
        width: 150
        running: false
    }

    InputPanel
    {
        id: inputPanel
        z: 99
        x: 0
        y: dialog.height
        width: dialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: dialog.height - inputPanel.height
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
}
