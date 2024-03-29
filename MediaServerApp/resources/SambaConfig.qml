import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1

import QtQuick.VirtualKeyboard 2.1
import SambaConfigLib 1.0


Dialog
{
    id: sambaConfigDialog
    visible: true
    width: parent.width
    height: parent.height - 40
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    property bool isEnabled: true

    Loader {
        anchors.fill:parent
        source:"ScreenSaverManager.qml";
    }

    SambaConfigView
    {
        id: sambaConfig
    }

    MessageDialog {
        id: fileErrorMessage
        title: "Warning"
        icon: StandardIcon.Warning
        text: "Samba confg file doesn't exist!"
        standardButtons: StandardButton.Close
        onButtonClicked: sambaConfigDialog.close()
    }

    FileDialog {
        id: fileDialog
        width: parent.width
        height: parent.height
        folder: shortcuts.home
        selectFolder: true
        onAccepted:
        {
            sambaConfig.bFileDialog_onAccepted(fileDialog.folder)
            sambaConfigDialog.visible=true
        }
        onRejected:
        {
            sambaConfigDialog.visible=true
        }
    }

    FileDialog {
        id: fileDialog1
        width: parent.width
        height: parent.height
        folder: shortcuts.home
        selectFolder: true
        onAccepted:
        {
            sambaConfig.bFileDialog1_onAccepted(fileDialog1.folder)
            sambaConfigDialog.visible=true
        }
        onRejected:
        {
            sambaConfigDialog.visible=true
        }
    }

    FileDialog {
        id: fileDialog2
        width: parent.width
        height: parent.height
        folder: shortcuts.home
        selectFolder: true
        onAccepted:
        {
            sambaConfig.bFileDialog2_onAccepted(fileDialog2.folder)
            sambaConfigDialog.visible=true
        }
        onRejected:
        {
            sambaConfigDialog.visible=true
        }
    }

    FileDialog {
        id: fileDialog3
        width: parent.width
        height: parent.height
        folder: shortcuts.home
        selectFolder: true
        onAccepted:
        {
            sambaConfig.bFileDialog3_onAccepted(fileDialog3.folder)
            sambaConfigDialog.visible=true
        }
        onRejected:
        {
            sambaConfigDialog.visible=true
        }
    }

    TabBar {
        id: tabBar
        width: parent.width
        TabButton {
            text: qsTr("Global")
        }
        TabButton {
            text: qsTr("Share 1")
        }
        TabButton {
            id: externalDisk1TabButton
            text: qsTr("Share 2")
        }
        TabButton {
            id: externalDisk2TabButton
            text: qsTr("Share 3")
        }
        TabButton {
            id: externalDisk3TabButton
            text: qsTr("Share 4")
        }
    }

    StackLayout
    {
        id: stackLayout
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        Item {
            id: globalTag
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    id: gridLayout
                    width: 446
                    rows: 5
                    columns: 2

                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    Text
                    {
                        id: workgroupText
                        width: 140
                        height: 40
                        text: qsTr("workgroup")
                        font.pixelSize: 18
                    }

                    TextField
                    {
                        id: workgroupTextField
                        width: 158
                        height: 40
                        onEditingFinished:
                        {
                            sambaConfig.tfWorkgroup_onEditingFinished(workgroupTextField.getText(0,workgroupTextField.length));
                        }
                    }

                    Text
                    {
                        id: serverStringText
                        width: 132
                        height: 40
                        text: qsTr("server string")
                        font.pixelSize: 18
                    }

                    TextField
                    {
                        id: serverStringTextField
                        width: 158
                        height: 40
                        onEditingFinished:
                        {
                            sambaConfig.tfServerString_onEditingFinished(serverStringTextField.getText(0,serverStringTextField.length));
                        }
                    }

                    Text
                    {
                        id: netbiosNameText
                        width: 132
                        height: 40
                        text: qsTr("netbios name")
                        font.pixelSize: 18
                    }

                    TextField
                    {
                        id: netbiosNameTextField
                        width: 158
                        height: 40
                        text: ""
                        onEditingFinished:
                        {
                            sambaConfig.tfNetbiosName_onEditingFinished(netbiosNameTextField.getText(0,netbiosNameTextField.length));
                        }
                    }

                    Text
                    {
                        id: securityText
                        width: 132
                        height: 40
                        text: qsTr("security")
                        font.pixelSize: 18
                    }

                    ComboBox
                    {
                        id: securityComboBox
                        Layout.preferredWidth: serverStringTextField.width
                        model: ListModel {

                            ListElement {
                                key: "user"
                            }
                            ListElement {
                                key: "share"
                            }
                        }
                        textRole: "key"

                        onDisplayTextChanged:
                        {
                            sambaConfig.cbSecurity_onDisplayTextChanged(securityComboBox.currentText);
                        }
                    }

                    Text
                    {
                        id: mapToGuestText
                        width: 132
                        height: 40
                        text: qsTr("map to guest")
                        font.pixelSize: 18
                    }


                    ComboBox
                    {
                        id: mapToGuestComboBox
                        Layout.preferredWidth: serverStringTextField.width
                        textRole: "key"
                        model: ListModel {
                            id:mapToGuestListModel
                            ListElement { key: "Bad User"; }
                            ListElement { key: "Bad Password";}
                            ListElement { key: "Never";}
                        }
                        onDisplayTextChanged:
                        {
                            sambaConfig.cbMapToGuest_onDisplayTextChanged(mapToGuestComboBox.currentText);
                        }
                    }
                }

                GridLayout {
                    id: gridLayout1
                    width: 192
                    columns: 1
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10
                    rowSpacing: 20
                    Layout.topMargin: 20


                    CheckBox {
                        id: globalBrowseableCheckBox
                        text: qsTr("browseable")
                        checkable: true
                        onClicked:
                        {
                            sambaConfig.cbGlobalBrowseable_onClicked(globalBrowseableCheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: localMasterCheckBox
                        text: qsTr("local master")
                        checkable: true
                        onClicked:
                        {
                            sambaConfig.cbLocalMaster_onClicked(localMasterCheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: domainMasterCheckBox
                        text: qsTr("domain master")
                        checkable: true
                        onClicked:
                        {
                            sambaConfig.cbDomainMaster_onClicked(domainMasterCheckBox.checked);
                        }
                    }
                }
            }
        }
        Item {
            id: localShareTab
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    id: gridLayout3
                    width: 348
                    rows: 4
                    columns: 3
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    Text {
                        id: nameText
                        width: 171
                        text: qsTr("Name")
                        Layout.preferredWidth: 140
                        wrapMode: Text.NoWrap
                        font.pixelSize: 18
                    }

                    TextField
                    {
                        id: nameTextField
                        width: 80
                        height: 20
                        Layout.columnSpan: 2
                        font.pixelSize: 18
                        onEditingFinished:
                        {
                            sambaConfig.tfName_onEditingFinished(nameTextField.getText(0,nameTextField.length));
                        }
                    }

                    Text {
                        id: tPath
                        text: qsTr("Path")
                        Layout.preferredWidth: nameText.width
                        font.pixelSize: nameText.font.pixelSize
                    }

                    TextField
                    {
                        id: pathTextField
                        readOnly: true
                        width: 80
                        height: 20
                        Layout.preferredWidth: nameTextField.width
                        font.pixelSize: nameTextField.font.pixelSize
                    }

                    Button {
                        id: bOpenCatalog
                        width: 87
                        text: "Open"
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.preferredWidth: 60
                        onClicked:
                        {
                            fileDialog.open()
                            sambaConfigDialog.visible=false
                        }
                    }

                    Text
                    {
                        id: createModeText
                        text: qsTr("Create Mode")
                        Layout.preferredWidth: nameText.width
                        font.pixelSize: nameText.font.pixelSize

                    }

                    TextField
                    {
                        id: createModeTextField
                        width: 80
                        height: 20
                        Layout.columnSpan: 2
                        Layout.preferredWidth: nameTextField.width
                        font.pixelSize: nameTextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfCreateMode_onEditingFinished(createModeTextField.getText(0,createModeTextField.length));
                        }
                    }

                    Text
                    {
                        id: directoryModeText
                        text: qsTr("Directory Mode")
                        wrapMode: Text.NoWrap
                        Layout.preferredWidth: nameText.width
                        font.pixelSize: nameText.font.pixelSize
                    }

                    TextField
                    {
                        id: directoryModeTextField
                        width: 80
                        height: 20
                        Layout.columnSpan: 2
                        Layout.preferredWidth: nameTextField.width
                        font.pixelSize: nameTextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfDirectoryMode_onEditingFinished(directoryModeTextField.getText(0,directoryModeTextField.length));
                        }
                    }
                }

                GridLayout {
                    id: gridLayout4
                    width: 192
                    rows: 4
                    columns: 1
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    CheckBox {
                        id: browseableCheckBox
                        text: qsTr("Browseable")
                        onClicked:
                        {
                            sambaConfig.chbBrowseable_onClicked(browseableCheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: writableCheckBox
                        text: qsTr("Writable")
                        onClicked:
                        {
                            sambaConfig.chbWritable_onClicked(writableCheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: guestOkCheckBox
                        text: qsTr("Guest ok")
                        onClicked:
                        {
                            sambaConfig.chbGuestOk_onClicked(guestOkCheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: readOnlyCheckBox
                        text: qsTr("Read only")
                        onClicked:
                        {
                            sambaConfig.chbReadOnly_onClicked(readOnlyCheckBox.checked);
                        }
                    }
                }
            }
        }
        Item {
            id: externalDisk1Tab
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    id: gridLayout5
                    height: 280
                    columns: 3
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    Text {
                        id: name1Text
                        width: 171
                        text: qsTr("Name")
                        Layout.preferredWidth: 140
                        font.pixelSize: 18
                        wrapMode: Text.NoWrap
                    }

                    TextField {
                        id: name1TextField
                        width: 80
                        height: 20
                        font.pixelSize: 18
                        Layout.columnSpan: 2
                        onEditingFinished:
                        {
                            sambaConfig.tfName1_onEditingFinished(name1TextField.getText(0,name1TextField.length));
                        }
                    }

                    Text {
                        id: path1Text
                        text: qsTr("Path")
                        Layout.preferredWidth: name1Text.width
                        font.pixelSize: name1Text.font.pixelSize
                    }

                    TextField {
                        id: path1TextField
                        width: 80
                        height: 20

                        Layout.preferredWidth: name1TextField.width
                        font.pixelSize: name1TextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfPath1_onEditingFinished(path1TextField.getText(0,path1TextField.length));
                        }
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
                            sambaConfigDialog.visible=false
                        }
                    }

                    Text {
                        id: createMode1Text
                        text: qsTr("Create Mode")
                        Layout.preferredWidth: name1Text.width
                        font.pixelSize: name1Text.font.pixelSize
                    }

                    TextField {
                        id: createMode1TextField
                        width: 80
                        height: 20
                        Layout.columnSpan: 2
                        Layout.preferredWidth: name1TextField.width
                        font.pixelSize: name1TextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfCreateMode1_onEditingFinished(name1TextField.getText(0,createMode1TextField.length));
                        }
                    }

                    Text {
                        id: directoryMode1Text
                        text: qsTr("Directory Mode")
                        Layout.preferredWidth: name1Text.width
                        font.pixelSize: name1Text.font.pixelSize
                        wrapMode: Text.NoWrap
                    }

                    TextField {
                        id: directoryMode1TextField
                        width: 80
                        height: 20
                        Layout.columnSpan: 2
                        Layout.preferredWidth: name1TextField.width
                        font.pixelSize: name1TextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfDirectoryMode1_onEditingFinished(directoryMode1TextField.getText(0,directoryMode1TextField.length));
                        }
                    }
                    rows: 4
                }

                GridLayout {
                    id: gridLayout6
                    width: 192
                    columns: 1
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    CheckBox {
                        id: browseable1CheckBox
                        text: qsTr("Browseable")
                        onClicked:
                        {
                            sambaConfig.chbBrowseable1_onClicked(browseable1CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: writable1CheckBox
                        text: qsTr("Writable")
                        onClicked:
                        {
                            sambaConfig.chbWritable1_onClicked(writable1CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: guestOk1CheckBox
                        text: qsTr("Guest ok")
                        onClicked:
                        {
                            sambaConfig.chbGuestOk1_onClicked(guestOk1CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: readOnly1CheckBox
                        text: qsTr("Read only")
                        onClicked:
                        {
                            sambaConfig.chbReadOnly1_onClicked(readOnly1CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: enabled1CheckBox
                        text: qsTr("Enabled")
                    }

                    rows: 5
                }
            }
        }
        Item {
            id: externalDisk2Tab
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    id: gridLayout7
                    width: 348
                    columns: 3
                    rows: 4
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    Text {
                        id: tName2
                        width: 171
                        text: qsTr("Name")
                        Layout.preferredWidth: 140
                        font.pixelSize: 18
                        wrapMode: Text.NoWrap
                    }

                    TextField {
                        id: name2TextField
                        width: 80
                        height: 20
                        font.pixelSize: 18
                        Layout.columnSpan: 2
                        onEditingFinished:
                        {
                            sambaConfig.tfName2_onEditingFinished(name2TextField.getText(0,name2TextField.length));
                        }
                    }

                    Text {
                        id: tPath2
                        text: qsTr("Path")
                        Layout.preferredWidth: tName2.width
                        font.pixelSize: tName2.font.pixelSize
                    }



                    TextField {
                        id: path2TextField
                        width: 80
                        height: 20
                        Layout.preferredWidth: name2TextField.width
                        font.pixelSize: name2TextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfPath2_onEditingFinished(path2TextField.getText(0,path2TextField.length));
                        }
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
                            sambaConfigDialog.visible=false
                        }
                    }
                    Text {
                        id: tCreateMode2
                        text: qsTr("Create Mode")
                        Layout.preferredWidth: tName2.width
                        font.pixelSize: tName2.font.pixelSize
                    }

                    TextField {
                        id: createMode2TextField
                        width: 80
                        height: 20
                        Layout.preferredWidth: name2TextField.width
                        font.pixelSize: name2TextField.font.pixelSize
                        Layout.columnSpan: 2
                        onEditingFinished:
                        {
                            sambaConfig.tfCreateMode2_onEditingFinished(createMode2TextField.getText(0,createMode2TextField.length));
                        }
                    }

                    Text {
                        id: tDirectoryMode2
                        text: qsTr("Directory Mode")
                        Layout.preferredWidth: tName2.width
                        font.pixelSize: tName2.font.pixelSize
                        wrapMode: Text.NoWrap
                    }

                    TextField {
                        id: directoryMode2TextField
                        width: 80
                        height: 20
                        Layout.preferredWidth: name2TextField.width
                        font.pixelSize: name2TextField.font.pixelSize
                        Layout.columnSpan: 2
                        onEditingFinished:
                        {
                            sambaConfig.tfDirectoryMode2_onEditingFinished(directoryMode2TextField.getText(0,directoryMode2TextField.length));
                        }
                    }

                }

                GridLayout {
                    id: gridLayout8
                    width: 192
                    columns: 1
                    rows: 5
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    CheckBox {
                        id: browseable2CheckBox
                        text: qsTr("Browseable")
                        onClicked:
                        {
                            sambaConfig.chbBrowseable2_onClicked(browseable2CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: writable2CheckBox
                        text: qsTr("Writable")
                        onClicked:
                        {
                            sambaConfig.chbWritable2_onClicked(writable2CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: guestOk2CheckBox
                        text: qsTr("Guest ok")
                        onClicked:
                        {
                            sambaConfig.chbGuestOk2_onClicked(guestOk2CheckBox);
                        }
                    }

                    CheckBox {
                        id: readOnly2CheckBox
                        text: qsTr("Read only")
                        onClicked:
                        {
                            sambaConfig.chbReadOnly2_onClicked(readOnly2CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: enabled2CheckBox
                        text: qsTr("Enabled")
                    }

                }
            }
        }
        Item {
            id: externalDisk3Tab
            RowLayout{
                y:51
                anchors.left: parent.left
                anchors.right: parent.right

                GridLayout {
                    id: gridLayout9
                    width: 348
                    columns: 3
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    Text {
                        id: tName3
                        width: 171
                        text: qsTr("Name")
                        Layout.preferredWidth: 140
                        font.pixelSize: 18
                        wrapMode: Text.NoWrap
                    }

                    TextField {
                        id: name3TextField
                        width: 80
                        height: 20
                        font.pixelSize: 18
                        Layout.columnSpan: 2
                        onEditingFinished:
                        {
                            sambaConfig.tfName3_onEditingFinished(name3TextField.getText(0,name3TextField.length));
                        }

                    }

                    Text {
                        id: tPath3
                        text: qsTr("Path")
                        Layout.preferredWidth: tName3.width
                        font.pixelSize: tName3.font.pixelSize
                    }

                    TextField {
                        id: path3TextField
                        width: 80
                        height: 20
                        Layout.preferredWidth: name3TextField.width
                        font.pixelSize: name3TextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfPath3_onEditingFinished(path3TextField.getText(0,path3TextField.length));
                        }
                    }

                    Button {
                        id: bOpenCatalog3
                        width: 87
                        text: "Open"
                        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                        Layout.preferredWidth: 60
                        onClicked:
                        {
                            fileDialog3.open()
                            sambaConfigDialog.visible=false
                        }
                    }

                    Text {
                        id: tCreateMode3
                        text: qsTr("Create Mode")
                        Layout.preferredWidth: tName3.width
                        font.pixelSize: tName3.font.pixelSize
                    }

                    TextField {
                        id: createMode3TextField
                        width: 80
                        height: 20
                        Layout.columnSpan: 2
                        Layout.preferredWidth: name3TextField.width
                        font.pixelSize: name3TextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfCreateMode3_onEditingFinished(createMode3TextField.getText(0,createMode3TextField.length));
                        }
                    }

                    Text {
                        id: tDirectoryMode3
                        text: qsTr("Directory Mode")
                        Layout.preferredWidth: tName3.width
                        font.pixelSize: tName3.font.pixelSize
                        wrapMode: Text.NoWrap
                    }

                    TextField {
                        id: directoryMode3TextField
                        width: 80
                        height: 20
                        Layout.columnSpan: 2
                        Layout.preferredWidth: name3TextField.width
                        font.pixelSize: name3TextField.font.pixelSize
                        onEditingFinished:
                        {
                            sambaConfig.tfDirectoryMode3_onEditingFinished(directoryMode3TextField.getText(0,directoryMode3TextField.length));
                        }
                    }
                    rows: 4
                }

                GridLayout {
                    id: gridLayout10
                    width: 192
                    columns: 1
                    rowSpacing: 20
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                    Layout.leftMargin: 10
                    Layout.topMargin: 20
                    Layout.rightMargin: 10

                    CheckBox {
                        id: browseable3CheckBox
                        text: qsTr("Browseable")
                        onClicked:
                        {
                            sambaConfig.chbBrowseable3_onClicked(browseable3CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: writable3CheckBox
                        text: qsTr("Writable")
                        onClicked:
                        {
                            sambaConfig.chbWritable3_onClicked(writable3CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: guestOk3CheckBox
                        text: qsTr("Guest ok")
                        onClicked:
                        {
                            sambaConfig.chbGuestOk3_onClicked(guestOk3CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: readOnly3CheckBox
                        text: qsTr("Read only")
                        onClicked:
                        {
                            sambaConfig.chbReadOnly3_onClicked(readOnly3CheckBox.checked);
                        }
                    }

                    CheckBox {
                        id: enabled3CheckBox
                        text: qsTr("Enabled")
                    }

                    rows: 5
                }
            }
        }
    }
    RowLayout {
        id: rowLayout
        anchors.bottomMargin: 20
        anchors.rightMargin: 20
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Button
        {
            id:restoreToDefaultButton
            text: "Restore Default"
            checked: false
            width: 160
            height: 40
            enabled: isEnabled
            onClicked:
            {
                workgroupTextField.text="WORKGROUP"
                serverStringTextField.text="SambaServer"
                netbiosNameTextField.text="DataServer"
                browseableCheckBox.checked=true
                localMasterCheckBox.checked=true
                domainMasterCheckBox.checked=true
                securityComboBox.currentIndex=0
                mapToGuestComboBox.currentIndex=0
                sambaConfig.tfWorkgroup_onEditingFinished(workgroupTextField.getText(0,workgroupTextField.length));
                sambaConfig.tfServerString_onEditingFinished(serverStringTextField.getText(0,serverStringTextField.length));
                sambaConfig.tfNetbiosName_onEditingFinished(netbiosNameTextField.getText(0,netbiosNameTextField.length));
                sambaConfig.cbSecurity_onDisplayTextChanged(securityComboBox.currentText);
                sambaConfig.cbMapToGuest_onDisplayTextChanged(mapToGuestComboBox.currentText);
                sambaConfig.cbGlobalBrowseable_onClicked(globalBrowseableCheckBox.checked);
                sambaConfig.cbLocalMaster_onClicked(localMasterCheckBox.checked);
                sambaConfig.cbDomainMaster_onClicked(domainMasterCheckBox.checked);
            }
        }

        Button
        {
            id:saveButton
            width: 160
            height: 40
            text: "Save"
            enabled: isEnabled
            onClicked:
            {
                sambaConfig.bSave_onClicked();
            }
            onPressed: { busySambaConfig.running=true }
            onReleased:{ busySambaConfig.running=false }
        }

        Button
        {
            text: "Close"
            width: 160
            height: 40
            onClicked:
            {
                sambaConfigDialog.close()
            }
        }
    }

    InputPanel
    {
        id: inputPanel
        y: sambaConfigDialog.height + 40
        width: sambaConfigDialog.width

        states: State
        {
            name: "visible"
            when: inputPanel.active
            PropertyChanges
            {
                target: inputPanel
                y: sambaConfigDialog.parent.height - inputPanel.height
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

    BusyIndicator
    {
        id: busySambaConfig
        anchors.centerIn: parent
        height: 100
        width: 100
        running: false
    }


    Component.onCompleted:
    {
        if (sambaConfig.fileValid)
        {
          sambaConfig.setStackLayout(stackLayout);
        sambaConfig.setWorkGroupTextField(workgroupTextField);
        sambaConfig.setServerStringTextField(serverStringTextField);
        sambaConfig.setNetBiosTextField(netbiosNameTextField);
        sambaConfig.setGlobalBrowsableCheckBox(globalBrowseableCheckBox);
        sambaConfig.setLocalMasterCheckBox(localMasterCheckBox);
        sambaConfig.setDomainMasterCheckBox(domainMasterCheckBox);
        sambaConfig.setSecurityComboBox(securityComboBox);
        sambaConfig.setMapToGuestComboBox(mapToGuestComboBox);

        sambaConfig.setCommentTextField(nameTextField);
        sambaConfig.setPathTextField(pathTextField);
        sambaConfig.setCreateModeTextField(createModeTextField);
        sambaConfig.setDirectoryModeTextField(directoryModeTextField);
        sambaConfig.setBrowsableCheckBox(browseableCheckBox);
        sambaConfig.setWritablecheckBox(writableCheckBox);
        sambaConfig.setGuestOkCheckBox(guestOkCheckBox);
        sambaConfig.setReadOnlyCheckBox(readOnlyCheckBox);


        sambaConfig.setCommentTextField1(name1TextField);
        sambaConfig.setPathTextField1(path1TextField);
        sambaConfig.setCreateModeTextField1(createMode1TextField);
        sambaConfig.setDirectoryModeTextField1(directoryMode1TextField);
        sambaConfig.setBrowsableCheckBox1(browseable1CheckBox);
        sambaConfig.setWritablecheckBox1(writable1CheckBox);
        sambaConfig.setGuestOkCheckBox1(guestOk1CheckBox);
        sambaConfig.setReadOnlyCheckBox1(readOnly1CheckBox);
        sambaConfig.setEnabled1(enabled1CheckBox);

        sambaConfig.setCommentTextField2(name2TextField);
        sambaConfig.setPathTextField2(path2TextField);
        sambaConfig.setCreateModeTextField2(createMode2TextField);
        sambaConfig.setDirectoryModeTextField2(directoryMode2TextField);
        sambaConfig.setBrowsableCheckBox2(browseable2CheckBox);
        sambaConfig.setWritablecheckBox2(writable2CheckBox);
        sambaConfig.setGuestOkCheckBox2(guestOk2CheckBox);
        sambaConfig.setReadOnlyCheckBox2(readOnly2CheckBox);
        sambaConfig.setEnabled2(enabled2CheckBox);

        sambaConfig.setCommentTextField3(name3TextField);
        sambaConfig.setPathTextField3(path3TextField);
        sambaConfig.setCreateModeTextField3(createMode3TextField);
        sambaConfig.setDirectoryModeTextField3(directoryMode3TextField);
        sambaConfig.setBrowsableCheckBox3(browseable3CheckBox);
        sambaConfig.setWritablecheckBox3(writable3CheckBox);
        sambaConfig.setGuestOkCheckBox3(guestOk3CheckBox);
        sambaConfig.setReadOnlyCheckBox3(readOnly3CheckBox);
        sambaConfig.setEnabled3(enabled3CheckBox);

        sambaConfig.loadAllConfigs(sambaConfigDialog);

        }
        else
        {
            fileErrorMessage.setVisible(true)
        }
   }
}
