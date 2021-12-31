import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import SettingsLib 1.0
import SettingsScreensaverLib 1.0
import SettingsPackagesLib 1.0

Dialog
{
    id: settingsDialog
    visible: true
    width: parent.width
    height: parent.height - 40
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    Settings
    {
        id: settings
    }

    SettingsScreensaver
    {
        id:settingsScreensaver
    }

    SettingsPackages
    {
        id:settingsPackages
    }

    Loader {
        anchors.fill:parent
        source:"screensavermanager.qml"
    }

    FileDialog {
        id: screenSaverFileDialog
        width: parent.width
        height: parent.height
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
        TabButton{
            text: qsTr("IP Address")

        }
        TabButton {
            text: qsTr("Screen Saver")
        }

        TabButton {
            text: qsTr("Update")
        }
    }

    StackLayout
    {
        id: stackLayout
        currentIndex: tabBar.currentIndex
        anchors.fill: parent

        Item
        {
            id: statusTag
            Layout.fillWidth: true
            Layout.preferredWidth: parent.width

            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    width: 352
                    rows: 8
                    columns: 3
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignHCenter
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10


                    Text {
                        id: tvHeadEndStatusText
                        text: qsTr("TvHeadEnd")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: tvHeadEndStatusSwitch
                        text: qsTr("Auto Startup")
                        checked: false
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.tvHeadEndStatusSwitch_OnClicked(tvHeadEndStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Button {
                        id: tvHeadEndStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.tvHeadEndStatusButton_OnClicked(tvHeadEndStatusButton, tvHeadEndStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Text {
                        id: ympdStatusText
                        text: qsTr("Website Music Player")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: ympdStatusSwitch
                        text: qsTr("Auto Startup")
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.ympdStatusSwitch_OnClicked(ympdStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Button {
                        id: ympdStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.ympdStatusButton_OnClicked(ympdStatusButton, ympdStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Text {
                        id: mpdStatusText
                        text: qsTr("Music Player Daemon")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: mpdStatusSwitch
                        text: qsTr("Auto Startup")
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.mpdStatusSwitch_OnClicked(mpdStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Button {
                        id: mpdStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.mpdStatusButton_OnClicked(mpdStatusButton, mpdStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Text {
                        id: dlnaStatusText
                        text: qsTr("DLNA")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: dlnaStatusSwitch
                        text: qsTr("Auto Startup")
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.dlnaStatusSwitch_OnClicked(dlnaStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Button {
                        id: dlnaStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.dlnaStatusButton_OnClicked(dlnaStatusButton, dlnaStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }

                    Text {
                        id: sambaStatusText
                        text: qsTr("Samba")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: sambaStatusSwitch
                        text: qsTr("Auto Startup")
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.sambaStatusSwitch_OnClicked(sambaStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Button {
                        id: sambaStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.sambaStatusButton_OnClicked(sambaStatusButton, sambaStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Text {
                        id: fileBrowserStatusText
                        text: qsTr("File Browser")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: fileBrowserStatusSwitch
                        text: qsTr("Auto Startup")
                        checked: false
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.fileBrowserStatusSwitch_OnClicked(fileBrowserStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Button {
                        id: fileBrowserStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.fileBrowserStatusButton_OnClicked(fileBrowserStatusButton, fileBrowserStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Text {
                        id: ftpStatusText
                        text: qsTr("FTP")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: ftpStatusSwitch
                        text: qsTr("Auto Startup")
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.ftpStatusSwitch_OnClicked(ftpStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Button {
                        id: ftpStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.ftpStatusButton_OnClicked(ftpStatusButton, ftpStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Text {
                        id: torrentClientStatusText
                        text: qsTr("Torrent Web Client")
                        font.pixelSize: 16
                    }

                    Switch {
                        id: torrentClientStatusSwitch
                        text: qsTr("Auto Startup")
                        font.pointSize: 10
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.torrentClientStatusSwitch_OnClicked(torrentClientStatusSwitch.checked)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Button {
                        id: torrentClientStatusButton
                        text: qsTr("Stop")
                        Layout.preferredWidth: 70
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        onClicked:
                        {
                            settings.torrentClientStatusButton_OnClicked(torrentClientStatusButton, torrentClientStatusButton.text)
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                }

                GridLayout {
                    width: 270
                    rows: 2
                    columns: 1
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop


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
                        Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                        Layout.preferredWidth: 360
                        wrapMode: Text.WordWrap
                        font.family: "Tahoma"
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
        }

        Item
        {
            id: wifiSettingsTag
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    width: 352
                    rows: 5
                    columns: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10

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
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
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
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

                    }
                }

                GridLayout {
                    width: 352
                    rows: 2
                    columns: 1
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

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
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }

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
        }


        Item
        {

            id: ipaddressSettingsTag
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    width: 352
                    columns: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10

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
                    width: 362
                    rows: 2
                    columns: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10

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

            }

            RowLayout {
                id: rowLayout
                y: 376
                anchors.bottomMargin: 20
                anchors.rightMargin: 140
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                Button
                {
                    id: button7
                    text: "Save"
                    height: 40
                    onClicked:
                    {
                        settings.saveIpAddressConfiguration()
                    }
                    onPressed: { busySettings.running=true }
                    onReleased:{ busySettings.running=false }
                }
            }
        }

        Item
        {
            id: screensaverSettingsTag
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    rowSpacing: 28
                    rows: 4
                    Layout.preferredWidth: 300
                    columns: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10


                    Text {
                        text: qsTr("Start Time[min]")
                        font.pixelSize: 16
                    }

                    SpinBox {
                        id: startTimeSpinBox
                        width: 138
                        from: 1
                        to: 15
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
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        font.pointSize: 11
                    }

                    CheckBox {
                        id: randomCheckBox
                        text: qsTr("Random")
                        checkable: true
                    }
                }
                GridLayout
                {
                    rowSpacing: 28
                    rows: 4
                    Layout.preferredWidth: 300
                    columns: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10

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
                        id: openButton
                        text: qsTr("Open")
                        Layout.preferredWidth: 60

                        Layout.columnSpan: 2
                        onClicked:
                        {
                            screenSaverFileDialog.open()
                            settingsDialog.visible=false
                        }
                    }

                    Switch {
                        id: screensaverEnableSwitch
                        text: qsTr("Enable")
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.columnSpan: 2

                        onClicked:
                        {
                            settingsScreensaver.screenSaverEnableSwitch_OnClicked(screensaverEnableSwitch.checked)
                        }
                    }

                }
            }
            RowLayout {
                id: rowLayout2
                y: 376
                anchors.bottomMargin: 20
                anchors.rightMargin: 140
                anchors.right: parent.right
                anchors.bottom: parent.bottom

                Button
                {
                    id:saveScreenSaverButton
                    x: 559
                    y: 380
                    width: 100
                    height: 40
                    text: "Save"
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
                    Layout.columnSpan: 2
                    onClicked:
                    {
                        settingsScreensaver.bSaveScreenSaver_onClicked(timeOutSpinBox.value,pathScreenSaverTextField.text,startTimeSpinBox.value,randomCheckBox.checked)
                    }
                    onPressed: { busySettings.running=true }
                    onReleased:{ busySettings.running=false }
                }
            }
        }

        Item
        {
            id: updateTag
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

            GridLayout {
                id: gridLayout
                width: 378
                rows: 4
                columns: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10

                Text {
                    text: qsTr("Package")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    font.pixelSize: 25
                }

                ComboBox {
                    id: packageComboBox
                    Layout.fillWidth: true
                    onDisplayTextChanged:
                    {
                        settingsPackages.cbPackage_onDisplayTextChanged(packageComboBox.currentText, packageSpecificationTextField);
                    }
                }

                Button {
                    id: upgradeButton
                    text: qsTr("Upgrade")
                    Layout.rowSpan: 2
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.columnSpan: 2
                    enabled: false
                    onClicked:
                    {
                        settingsPackages.bUpgrade_onClicked(packageComboBox.currentText)
                        settingsPackages.bUpdate_onClicked(packageComboBox, packageSpecificationTextField);
                    }
                    onPressed: { busySettings.running=true }
                    onReleased:{ busySettings.running=false }
                }

                RowLayout {
                    id: rowLayout1
                    height: 100
                    Layout.preferredHeight: 50
                    Layout.preferredWidth: 300
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.columnSpan: 2

                    Button {
                        id: updateButton
                        text: qsTr("Update")
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        onClicked:
                        {
                            settingsPackages.bUpdate_onClicked(packageComboBox, packageSpecificationTextField);
                            upgradeAllButton.enabled=true;
                            upgradeButton.enabled=true;
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }

                    Button {
                        id: upgradeAllButton
                        text: qsTr("Upgrade all")
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        enabled: false
                        onClicked:
                        {
                            settingsPackages.bUpgradeAll_onClicked()
                            settingsPackages.bUpdate_onClicked(packageComboBox, packageSpecificationTextField);
                        }
                        onPressed: { busySettings.running=true }
                        onReleased:{ busySettings.running=false }
                    }
                }
            }

            GridLayout {
                id: gridLayout1
                width: 330
                rows: 2
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                Layout.leftMargin: 10
                Layout.rightMargin: 10

                Text {
                    text: qsTr("Package Specification")
                    horizontalAlignment: Text.AlignLeft

                    font.pixelSize: 25
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                }

                Text {
                    id: packageSpecificationTextField
                    wrapMode: Text.WordWrap
                    Layout.fillWidth: true
                    font.pixelSize: 10
                    Layout.fillHeight: true
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                }
                columns: 1
            }
        }
            }
    }

    RowLayout {
        id: rowLayout10
        y: 376
        spacing: 30
        anchors.bottomMargin: 20
        anchors.rightMargin: 20
        anchors.right: parent.right
        anchors.bottom: parent.bottom


        Button {
            height: 40
            text: "Close"
            onClicked:
            {
                settingsDialog.close()
            }
        }
    }

    BusyIndicator
    {
        id: busySettings
        anchors.centerIn: parent
        width: 100
        height: 100
        running: false
    }

    InputPanel
    {
        id: inputPanel
        y: settingsDialog.height + 40
        width: settingsDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: settingsDialog.parent.height - inputPanel.height
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
        settingsScreensaver.loadScreenSaverConfigurations(screensaverEnableSwitch,startTimeSpinBox,pathScreenSaverTextField,timeOutSpinBox,randomCheckBox)
        settings.checkTvHeadEndServiceStatus(tvHeadEndStatusSwitch,tvHeadEndStatusButton)
        settings.checkYMPDSystemdStatus(ympdStatusSwitch,ympdStatusButton)
        settings.checkMPDSystemdStatus(mpdStatusSwitch,mpdStatusButton)
        settings.checkDLNASystemdStatus(dlnaStatusSwitch,dlnaStatusButton)
        settings.checkSMBSystemdStatus(sambaStatusSwitch,sambaStatusButton)
        settings.checkFileBrowserSystemdStatus(fileBrowserStatusSwitch,fileBrowserStatusButton)
        settings.checkFTPSystemdStatus(ftpStatusSwitch,ftpStatusButton)
        settings.checkTorrentClientSystemdStatus(torrentClientStatusSwitch,torrentClientStatusButton)
    }
}


