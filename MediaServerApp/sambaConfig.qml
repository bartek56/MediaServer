import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import SambaConfigLib 1.0

Dialog
{
    id: dialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    SambaConfig
    {
        id: sambaConfig
    }

    TabBar {
        id: tabBar
        width: parent.width
        TabButton {
            text: qsTr("Global")
        }
        TabButton {
            text: qsTr("Local Share")
        }
        TabButton {
            id: tbExternalDisk1
            text: qsTr("External Disk 1")
            visible: false
        }
        TabButton {
            id: tbExternalDisk2
            text: qsTr("External Disk 2")
            visible: false
        }
        TabButton {
            id: tbExternalDisk3
            text: qsTr("External Disk 3")
            visible: false
        }
    }

    StackLayout {
        id: stackLayout
        width: parent.width
        currentIndex: tabBar.currentIndex
        Item {
            id: globalTag

            GridLayout {
                id: gridLayout1
                x: 531
                y: 62
                width: 192
                height: 292
                columns: 1

                CheckBox {
                    id: cbGlobalBrowseable
                    text: qsTr("browseable")
                    checkable: true
                    onClicked:
                    {
                        sambaConfig.cbGlobalBrowseable_onClicked(cbGlobalBrowseable.checked);
                    }
                }

                CheckBox {
                    id: cbLocalMaster
                    text: qsTr("local master")
                    checkable: true
                    onClicked:
                    {
                        sambaConfig.cbLocalMaster_onClicked(cbLocalMaster.checked);
                    }
                }

                CheckBox {
                    id: cbDomainMaster
                    text: qsTr("domain master")
                    checkable: true
                    onClicked:
                    {
                        sambaConfig.cbDomainMaster_onClicked(cbDomainMaster.checked);
                    }
                }
            }

            GridLayout {
                id: gridLayout
                x: 35
                y: 62
                width: 446
                height: 312
                rows: 5
                columns: 2

                Text
                {
                    id: lWorkgroup
                    width: 140
                    height: 40
                    text: qsTr("workgroup")
                    font.pixelSize: 18
                }

                TextField
                {
                    id: tfWorkgroup
                    width: 158
                    height: 40
                    onEditingFinished:
                    {
                        sambaConfig.tfWorkgroup_onEditingFinished(tfWorkgroup.getText(0,tfWorkgroup.length));
                    }
                }

                Text
                {
                    id: lServerString
                    width: 132
                    height: 40
                    text: qsTr("server string")
                    font.pixelSize: 18
                }

                TextField
                {
                    id: tfServerString
                    width: 158
                    height: 40
                    onEditingFinished:
                    {
                        sambaConfig.tfServerString_onEditingFinished(tfServerString.getText(0,tfServerString.length));
                    }
                }

                Text
                {
                    id: lNetbiosName
                    width: 132
                    height: 40
                    text: qsTr("netbios name")
                    font.pixelSize: 18
                }

                TextField
                {
                    id: tfNetbiosName
                    width: 158
                    height: 40
                    text: ""
                    onEditingFinished:
                    {
                        sambaConfig.tfNetbiosName_onEditingFinished(tfNetbiosName.getText(0,tfNetbiosName.length));
                    }
                }

                Text
                {
                    id: lSecurity
                    width: 132
                    height: 40
                    text: qsTr("security")
                    font.pixelSize: 18
                }

                ComboBox
                {
                    id: cbSecurity
                    Layout.preferredWidth: tfServerString.width
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
                        sambaConfig.cbSecurity_onDisplayTextChanged(cbSecurity.currentText);
                    }
                }

                Text
                {
                    id: lMapToGuest
                    width: 132
                    height: 40
                    text: qsTr("map to guest")
                    font.pixelSize: 18
                }


                ComboBox
                {
                    id: cbMapToGuest
                    Layout.preferredWidth: tfServerString.width
                    textRole: "key"
                    model: ListModel {
                        id:mapToGuestListModel
                        ListElement { key: "Bad User"; }
                        ListElement { key: "Bad Password";}
                        ListElement { key: "Never";}
                    }
                    onDisplayTextChanged:
                    {
                        sambaConfig.cbMapToGuest_onDisplayTextChanged(cbMapToGuest.currentText);
                    }
                }
            }
        }
        Item {
            id: localShareTab

            GridLayout {
                id: gridLayout3
                x: 51
                y: 70
                width: 348
                height: 280
                rows: 4
                columns: 2

                Text {
                    id: tName
                    width: 171
                    text: qsTr("Name")
                    Layout.preferredWidth: 140
                    wrapMode: Text.NoWrap
                    font.pixelSize: 18
                }

                TextField
                {
                    id: tfName
                    width: 80
                    height: 20
                    font.pixelSize: 18
                    onEditingFinished:
                    {
                        sambaConfig.tfName_onEditingFinished(tfName.getText(0,tfName.length));
                    }
                }

                Text {
                    id: tPath
                    text: qsTr("Path")
                    Layout.preferredWidth: tName.width
                    font.pixelSize: tName.font.pixelSize
                }

                TextField
                {
                    id: tfPath
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName.width
                    font.pixelSize: tfName.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfPath_onEditingFinished(tfName.getText(0,tfName.length));
                    }
                }

                Text
                {
                    id: tCreateMode
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tName.width
                    font.pixelSize: tName.font.pixelSize

                }

                TextField
                {
                    id: tfCreateMode
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName.width
                    font.pixelSize: tfName.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfCreateMode_onEditingFinished(tfCreateMode.getText(0,tfCreateMode.length));
                    }
                }

                Text
                {
                    id: tDirectoryMode
                    text: qsTr("Directory Mode")
                    wrapMode: Text.NoWrap
                    Layout.preferredWidth: tName.width
                    font.pixelSize: tName.font.pixelSize
                }

                TextField
                {
                    id: tfDirectoryMode
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName.width
                    font.pixelSize: tfName.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfDirectoryMode_onEditingFinished(tfDirectoryMode.getText(0,tfDirectoryMode.length));
                    }
                }
            }

            GridLayout {
                id: gridLayout4
                x: 531
                y: 62
                width: 192
                height: 292
                rows: 4
                columns: 1

                CheckBox {
                    id: chbBrowseable
                    text: qsTr("Browseable")
                    onClicked:
                    {
                        sambaConfig.chbBrowseable_onClicked(chbBrowseable.checked);
                    }
                }

                CheckBox {
                    id: chbWritable
                    text: qsTr("Writable")
                    onClicked:
                    {
                        sambaConfig.chbWritable_onClicked(chbWritable.checked);
                    }
                }

                CheckBox {
                    id: chbGuestOk
                    text: qsTr("Guest ok")
                    onClicked:
                    {
                        sambaConfig.chbGuestOk_onClicked(chbGuestOk.checked);
                    }
                }

                CheckBox {
                    id: chbReadOnly
                    text: qsTr("Read only")
                    onClicked:
                    {
                        sambaConfig.chbReadOnly_onClicked(chbReadOnly.checked);
                    }
                }
            }
        }

        Item {
            id: externalDisk1Tab
            GridLayout {
                id: gridLayout5
                x: 51
                y: 70
                width: 348
                height: 280
                columns: 2
                Text {
                    id: tName1
                    width: 171
                    text: qsTr("Name")
                    Layout.preferredWidth: 140
                    font.pixelSize: 18
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfName1
                    width: 80
                    height: 20
                    font.pixelSize: 18
                    onEditingFinished:
                    {
                        sambaConfig.tfName1_onEditingFinished(tfName1.getText(0,tfName1.length));
                    }
                }

                Text {
                    id: tPath1
                    text: qsTr("Path")
                    Layout.preferredWidth: tName1.width
                    font.pixelSize: tName1.font.pixelSize
                }

                TextField {
                    id: tfPath1
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName1.width
                    font.pixelSize: tfName1.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfPath1_onEditingFinished(tfPath1.getText(0,tfPath1.length));
                    }
                }

                Text {
                    id: tCreateMode1
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tName1.width
                    font.pixelSize: tName1.font.pixelSize
                }

                TextField {
                    id: tfCreateMode1
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName1.width
                    font.pixelSize: tfName1.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfCreateMode1_onEditingFinished(tfName1.getText(0,tfCreateMode1.length));
                    }
                }

                Text {
                    id: tDirectoryMode1
                    text: qsTr("Directory Mode")
                    Layout.preferredWidth: tName1.width
                    font.pixelSize: tName1.font.pixelSize
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfDirectoryMode1
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName1.width
                    font.pixelSize: tfName1.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfDirectoryMode1_onEditingFinished(tfDirectoryMode1.getText(0,tfDirectoryMode1.length));
                    }
                }
                rows: 4
            }

            GridLayout {
                id: gridLayout6
                x: 530
                y: 48
                width: 192
                height: 312
                columns: 1
                CheckBox {
                    id: chbBrowseable1
                    text: qsTr("Browseable")
                    onClicked:
                    {
                        sambaConfig.chbBrowseable1_onClicked(chbBrowseable1.checked);
                    }
                }

                CheckBox {
                    id: chbWritable1
                    text: qsTr("Writable")
                    onClicked:
                    {
                        sambaConfig.chbWritable1_onClicked(chbWritable1.checked);
                    }
                }

                CheckBox {
                    id: chbGuestOk1
                    text: qsTr("Guest ok")
                    onClicked:
                    {
                        sambaConfig.chbbGuestOk1_onClicked(chbGuestOk1.checked);
                    }
                }

                CheckBox {
                    id: chbReadOnly1
                    text: qsTr("Read only")
                    onClicked:
                    {
                        sambaConfig.chbReadOnly_onClicked(chbReadOnly1.checked);
                    }
                }

                Button {
                    id: bUmount1
                    text: qsTr("umount")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    highlighted: true
                    onClicked:
                    {
                        sambaConfig.bUmount1_onClicked();
                    }
                }
                rows: 5
            }
        }
        Item {
            id: externalDisk2Tab

            GridLayout {
                id: gridLayout7
                x: 51
                y: 70
                width: 348
                height: 280
                columns: 2
                rows: 4
                Text {
                    id: tName2
                    width: 171
                    text: qsTr("Name")
                    Layout.preferredWidth: 140
                    font.pixelSize: 18
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfName2
                    width: 80
                    height: 20
                    font.pixelSize: 18
                    onEditingFinished:
                    {
                        sambaConfig.tfName2_onEditingFinished(tfName2.getText(0,tfName2.length));
                    }
                }

                Text {
                    id: tPath2
                    text: qsTr("Path")
                    Layout.preferredWidth: tName2.width
                    font.pixelSize: tName2.font.pixelSize
                }

                TextField {
                    id: tfPath2
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName2.width
                    font.pixelSize: tfName2.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfPath2_onEditingFinished(tfPath2.getText(0,tfPath2.length));
                    }
                }

                Text {
                    id: tCreateMode2
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tName2.width
                    font.pixelSize: tName2.font.pixelSize
                }

                TextField {
                    id: tfCreateMode2
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName2.width
                    font.pixelSize: tfName2.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfCreateMode2_onEditingFinished(tfCreateMode2.getText(0,tfCreateMode2.length));
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
                    id: tfDirectoryMode2
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName2.width
                    font.pixelSize: tfName2.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfDirectoryMode2_onEditingFinished(tfDirectoryMode2.getText(0,tfDirectoryMode2.length));
                    }
                }

            }

            GridLayout {
                id: gridLayout8
                x: 531
                y: 62
                width: 192
                height: 292
                columns: 1
                rows: 5
                CheckBox {
                    id: chbBrowseable2
                    text: qsTr("Browseable")
                    onClicked:
                    {
                        sambaConfig.chbBrowseable2_onClicked(chbBrowseable2.checked);
                    }
                }

                CheckBox {
                    id: chbWritable2
                    text: qsTr("Writable")
                    onClicked:
                    {
                        sambaConfig.chbWritable2_onClicked(chbWritable2.checked);
                    }
                }

                CheckBox {
                    id: chbGuestOk2
                    text: qsTr("Guest ok")
                    onClicked:
                    {
                        sambaConfig.chbGuestOk2_onClicked(chbGuestOk2);
                    }
                }

                CheckBox {
                    id: chbReadOnly2
                    text: qsTr("Read only")
                    onClicked:
                    {
                        sambaConfig.chbReadOnly2_onClicked(chbReadOnly2.checked);
                    }
                }

                Button {
                    id: bUmount2
                    text: qsTr("umount")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    highlighted: true
                    onClicked:
                    {
                        sambaConfig.bUmount2_onClicked();
                    }
                }
            }
        }
        Item {
            id: externalDisk3Tab
            GridLayout {
                id: gridLayout9
                x: 51
                y: 70
                width: 348
                height: 280
                columns: 2
                Text {
                    id: tName3
                    width: 171
                    text: qsTr("Name")
                    Layout.preferredWidth: 140
                    font.pixelSize: 18
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfName3
                    width: 80
                    height: 20
                    font.pixelSize: 18
                    onEditingFinished:
                    {
                        sambaConfig.tfName3_onEditingFinished(tfName3.getText(0,tfName3.length));
                    }

                }

                Text {
                    id: tPath3
                    text: qsTr("Path")
                    Layout.preferredWidth: tName3.width
                    font.pixelSize: tName3.font.pixelSize
                }

                TextField {
                    id: tfPath3
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName3.width
                    font.pixelSize: tfName3.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfPath3_onEditingFinished(tfPath3.getText(0,tfPath3.length));
                    }
                }

                Text {
                    id: tCreateMode3
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tName3.width
                    font.pixelSize: tName3.font.pixelSize
                }

                TextField {
                    id: tfCreateMode3
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName3.width
                    font.pixelSize: tfName3.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfCreateMode3_onEditingFinished(tfCreateMode3.getText(0,tfCreateMode3.length));
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
                    id: tfDirectoryMode3
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfName3.width
                    font.pixelSize: tfName3.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfDirectoryMode3_onEditingFinished(tfDirectoryMode3.getText(0,tfDirectoryMode3.length));
                    }
                }
                rows: 4
            }

            GridLayout {
                id: gridLayout10
                x: 531
                y: 62
                width: 192
                height: 292
                columns: 1
                CheckBox {
                    id: chbBrowseable3
                    text: qsTr("Browseable")
                    onClicked:
                    {
                        sambaConfig.chbBrowseable3_onClicked(chbBrowseable3.checked);
                    }
                }

                CheckBox {
                    id: chbWritable3
                    text: qsTr("Writable")
                    onClicked:
                    {
                        sambaConfig.chbWritable3_onClicked(chbWritable3.checked);
                    }
                }

                CheckBox {
                    id: chbGuestOk3
                    text: qsTr("Guest ok")
                    onClicked:
                    {
                        sambaConfig.chbGuestOk3_onClicked(chbGuestOk3.checked);
                    }
                }

                CheckBox {
                    id: chbReadOnly3
                    text: qsTr("Read only")
                    onClicked:
                    {
                        sambaConfig.chbReadOnly3_onClicked(chbReadOnly3.checked);
                    }
                }
                Button {
                    id: bUmount3
                    text: qsTr("umount")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    highlighted: true
                    onClicked:
                    {
                        sambaConfig.bUmount3_onClicked();
                    }
                }
                rows: 5
            }
        }

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

    RowLayout {
        id: rowLayout
        anchors.bottomMargin: 8
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        Button
        {
            text: "Restore Default"
            checked: false
            width: 160
            height: 40
            onClicked:
            {
                tfWorkgroup.text="WORKGROUP"
                tfServerString.text="SambaServer"
                tfNetbiosName.text="DataServer"
                chbBrowseable.checked=true
                cbLocalMaster.checked=true
                cbDomainMaster.checked=true
                cbSecurity.currentIndex=0
                cbMapToGuest.currentIndex=0
                sambaConfig.tfWorkgroup_onEditingFinished(tfWorkgroup.getText(0,tfWorkgroup.length));
                sambaConfig.tfServerString_onEditingFinished(tfServerString.getText(0,tfServerString.length));
                sambaConfig.tfNetbiosName_onEditingFinished(tfNetbiosName.getText(0,tfNetbiosName.length));
                sambaConfig.cbSecurity_onDisplayTextChanged(cbSecurity.currentText);
                sambaConfig.cbMapToGuest_onDisplayTextChanged(cbMapToGuest.currentText);
                sambaConfig.cbGlobalBrowseable_onClicked(cbGlobalBrowseable.checked);
                sambaConfig.cbLocalMaster_onClicked(cbLocalMaster.checked);
                sambaConfig.cbDomainMaster_onClicked(cbDomainMaster.checked);
            }
        }

        Button
        {
            width: 160
            height: 40
            text: "Save"
            onClicked:
            {
                sambaConfig.bSave_onClicked();
            }
        }

        Button
        {
            text: "Close"
            width: 160
            height: 40
            onClicked:
            {
                dialog.close()
            }
        }
    }

    Component.onCompleted:
    {
        sambaConfig.setStackLayout(stackLayout);

        sambaConfig.setWorkGroupTextField(tfWorkgroup);
        sambaConfig.setServerStringTextField(tfServerString);
        sambaConfig.setNetBiosTextField(tfNetbiosName);
        sambaConfig.setGlobalBrowsableCheckBox(cbGlobalBrowseable);
        sambaConfig.setLocalMasterCheckBox(cbLocalMaster);
        sambaConfig.setDomainMasterCheckBox(cbDomainMaster);
        sambaConfig.setSecurityComboBox(cbSecurity);
        sambaConfig.setMapToGuestComboBox(cbMapToGuest);

        sambaConfig.setCommentTextField(tfName);
        sambaConfig.setPathTextField(tfPath);
        sambaConfig.setCreateModeTextField(tfCreateMode);
        sambaConfig.setDirectoryModeTextField(tfDirectoryMode);
        sambaConfig.setBrowsableCheckBox(chbBrowseable);
        sambaConfig.setWritablecheckBox(chbWritable);
        sambaConfig.setGuestOkCheckBox(chbGuestOk);
        sambaConfig.setReadOnlyCheckBox(chbReadOnly);


        sambaConfig.setCommentTextField1(tfName1);
        sambaConfig.setPathTextField1(tfPath1);
        sambaConfig.setCreateModeTextField1(tfCreateMode1);
        sambaConfig.setDirectoryModeTextField1(tfDirectoryMode1);
        sambaConfig.setBrowsableCheckBox1(chbBrowseable1);
        sambaConfig.setWritablecheckBox1(chbWritable1);
        sambaConfig.setGuestOkCheckBox1(chbGuestOk1);
        sambaConfig.setReadOnlyCheckBox1(chbReadOnly1);

        sambaConfig.setCommentTextField2(tfName2);
        sambaConfig.setPathTextField2(tfPath2);
        sambaConfig.setCreateModeTextField2(tfCreateMode2);
        sambaConfig.setDirectoryModeTextField2(tfDirectoryMode2);
        sambaConfig.setBrowsableCheckBox2(chbBrowseable2);
        sambaConfig.setWritablecheckBox2(chbWritable2);
        sambaConfig.setGuestOkCheckBox2(chbGuestOk2);
        sambaConfig.setReadOnlyCheckBox2(chbReadOnly2);

        sambaConfig.setCommentTextField3(tfName3);
        sambaConfig.setPathTextField3(tfPath3);
        sambaConfig.setCreateModeTextField3(tfCreateMode3);
        sambaConfig.setDirectoryModeTextField3(tfDirectoryMode3);
        sambaConfig.setBrowsableCheckBox3(chbBrowseable3);
        sambaConfig.setWritablecheckBox3(chbWritable3);
        sambaConfig.setGuestOkCheckBox3(chbGuestOk3);
        sambaConfig.setReadOnlyCheckBox3(chbReadOnly3);

        sambaConfig.setExternalDiskTabButton1(tbExternalDisk1);
        sambaConfig.setExternalDiskTabButton2(tbExternalDisk2);
        sambaConfig.setExternalDiskTabButton3(tbExternalDisk3);
        sambaConfig.checkExternalDisks();
        sambaConfig.openFile();
    }
}
