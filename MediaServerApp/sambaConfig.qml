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
    property alias globalTag: globalTag
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    SambaConfig
    {
        id:sambaConfig
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
            text: qsTr("External Device 1")
        }
        TabButton {
            text: qsTr("External Device 2")
        }
        TabButton {
            text: qsTr("External Device 3")
        }

        GridLayout {
            id: gridLayout2
            width: 100
            height: 100
        }
    }

    StackLayout {
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
                    id: tComment
                    width: 171
                    text: qsTr("Comment")
                    Layout.preferredWidth: 140
                    wrapMode: Text.NoWrap
                    font.pixelSize: 18
                }

                TextField
                {
                    id: tfComment
                    width: 80
                    height: 20
                    font.pixelSize: 18
                    onEditingFinished:
                    {
                        sambaConfig.tfComment_onEditingFinished(tfComment.getText(0,tfComment.length));
                    }
                }

                Text {
                    id: tPath
                    text: qsTr("Path")
                    Layout.preferredWidth: tComment.width
                    font.pixelSize: tComment.font.pixelSize
                }

                TextField
                {
                    id: tfPath
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment.width
                    font.pixelSize: tfComment.font.pixelSize
                    onEditingFinished:
                    {
                        sambaConfig.tfPath_onEditingFinished(tfComment.getText(0,tfComment.length));
                    }
                }

                Text
                {
                    id: tCreateMode
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tComment.width
                    font.pixelSize: tComment.font.pixelSize

                }

                TextField
                {
                    id: tfCreateMode
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment.width
                    font.pixelSize: tfComment.font.pixelSize
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
                    Layout.preferredWidth: tComment.width
                    font.pixelSize: tComment.font.pixelSize
                }

                TextField
                {
                    id: tfDirectoryMode
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment.width
                    font.pixelSize: tfComment.font.pixelSize
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
            id: externalDevice1Tab

            GridLayout {
                id: gridLayout5
                x: 51
                y: 70
                width: 348
                height: 280
                columns: 2
                Text {
                    id: tComment1
                    width: 171
                    text: qsTr("Comment")
                    Layout.preferredWidth: 140
                    font.pixelSize: 18
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfComment1
                    width: 80
                    height: 20
                    font.pixelSize: 18
                }

                Text {
                    id: tPath1
                    text: qsTr("Path")
                    Layout.preferredWidth: tComment1.width
                    font.pixelSize: tComment1.font.pixelSize
                }

                TextField {
                    id: tfPath1
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment1.width
                    font.pixelSize: tfComment1.font.pixelSize
                }

                Text {
                    id: tCreateMode1
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tComment1.width
                    font.pixelSize: tComment1.font.pixelSize
                }

                TextField {
                    id: tfCreateMode1
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment1.width
                    font.pixelSize: tfComment1.font.pixelSize
                }

                Text {
                    id: tDirectoryMode1
                    text: qsTr("Directory Mode")
                    Layout.preferredWidth: tComment1.width
                    font.pixelSize: tComment1.font.pixelSize
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfDirectoryMode1
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment1.width
                    font.pixelSize: tfComment1.font.pixelSize
                }
                rows: 4
            }

            GridLayout {
                id: gridLayout6
                x: 531
                y: 62
                width: 192
                height: 292
                columns: 1
                CheckBox {
                    id: chbBrowseable1
                    text: qsTr("Browseable")
                }

                CheckBox {
                    id: chbWritable1
                    text: qsTr("Writable")
                }

                CheckBox {
                    id: chBGuestOk1
                    text: qsTr("Guest ok")
                }

                CheckBox {
                    id: chbReadOnly1
                    text: qsTr("Read only")
                }
                rows: 4
            }
        }
        Item {
            id: externalDevice2Tab

            GridLayout {
                id: gridLayout7
                x: 51
                y: 70
                width: 348
                height: 280
                columns: 2
                rows: 4
                Text {
                    id: tComment2
                    width: 171
                    text: qsTr("Comment")
                    Layout.preferredWidth: 140
                    font.pixelSize: 18
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfComment2
                    width: 80
                    height: 20
                    font.pixelSize: 18
                }

                Text {
                    id: tPath2
                    text: qsTr("Path")
                    Layout.preferredWidth: tComment2.width
                    font.pixelSize: tComment2.font.pixelSize
                }

                TextField {
                    id: tfPath2
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment2.width
                    font.pixelSize: tfComment2.font.pixelSize
                }

                Text {
                    id: tCreateMode2
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tComment2.width
                    font.pixelSize: tComment2.font.pixelSize
                }

                TextField {
                    id: tfCreateMode2
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment2.width
                    font.pixelSize: tfComment2.font.pixelSize
                }

                Text {
                    id: tDirectoryMode2
                    text: qsTr("Directory Mode")
                    Layout.preferredWidth: tComment2.width
                    font.pixelSize: tComment2.font.pixelSize
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfDirectoryMode2
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment2.width
                    font.pixelSize: tfComment2.font.pixelSize
                }

            }

            GridLayout {
                id: gridLayout8
                x: 531
                y: 62
                width: 192
                height: 292
                columns: 1
                rows: 4
                CheckBox {
                    id: chbBrowseable2
                    text: qsTr("Browseable")
                }

                CheckBox {
                    id: chbWritable2
                    text: qsTr("Writable")
                }

                CheckBox {
                    id: chBGuestOk2
                    text: qsTr("Guest ok")
                }

                CheckBox {
                    id: chbReadOnly2
                    text: qsTr("Read only")
                }
            }
        }
        Item {
            id: externalDevice3Tab

            GridLayout {
                id: gridLayout9
                x: 51
                y: 70
                width: 348
                height: 280
                columns: 2
                Text {
                    id: tComment3
                    width: 171
                    text: qsTr("Comment")
                    Layout.preferredWidth: 140
                    font.pixelSize: 18
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfComment3
                    width: 80
                    height: 20
                    font.pixelSize: 18
                }

                Text {
                    id: tPath3
                    text: qsTr("Path")
                    Layout.preferredWidth: tComment3.width
                    font.pixelSize: tComment3.font.pixelSize
                }

                TextField {
                    id: tfPath3
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment3.width
                    font.pixelSize: tfComment3.font.pixelSize
                }

                Text {
                    id: tCreateMode3
                    text: qsTr("Create Mode")
                    Layout.preferredWidth: tComment3.width
                    font.pixelSize: tComment3.font.pixelSize
                }

                TextField {
                    id: tfCreateMode3
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment3.width
                    font.pixelSize: tfComment3.font.pixelSize
                }

                Text {
                    id: tDirectoryMode3
                    text: qsTr("Directory Mode")
                    Layout.preferredWidth: tComment3.width
                    font.pixelSize: tComment3.font.pixelSize
                    wrapMode: Text.NoWrap
                }

                TextField {
                    id: tfDirectoryMode3
                    width: 80
                    height: 20
                    Layout.preferredWidth: tfComment3.width
                    font.pixelSize: tfComment3.font.pixelSize
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
                }

                CheckBox {
                    id: chbWritable3
                    text: qsTr("Writable")
                }

                CheckBox {
                    id: chBGuestOk3
                    text: qsTr("Guest ok")
                }

                CheckBox {
                    id: chbReadOnly3
                    text: qsTr("Read only")
                }
                rows: 4
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
                cbBrowseable.checked=true
                cbLocalMaster.checked=true
                cbDomainMaster.checked=true
                cbSecurity.currentIndex=0
                cbMapToGuest.currentIndex=0
                sambaConfig.tfWorkgroup_onEditingFinished(tfWorkgroup.getText(0,tfWorkgroup.length));
                sambaConfig.tfServerString_onEditingFinished(tfServerString.getText(0,tfServerString.length));
                sambaConfig.tfNetbiosName_onEditingFinished(tfNetbiosName.getText(0,tfNetbiosName.length));
                sambaConfig.cbSecurity_onDisplayTextChanged(cbSecurity.currentText);
                sambaConfig.cbMapToGuest_onDisplayTextChanged(cbMapToGuest.currentText);
                sambaConfig.cbBrowseable_onClicked(cbGlobalBrowseable.checked);
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
        sambaConfig.setWorkGroupTextField(tfWorkgroup);
        sambaConfig.setServerStringTextField(tfServerString);
        sambaConfig.setNetBiosTextField(tfNetbiosName);
        sambaConfig.setGlobalBrowsableCheckBox(cbGlobalBrowseable);
        sambaConfig.setLocalMasterCheckBox(cbLocalMaster);
        sambaConfig.setDomainMasterCheckBox(cbDomainMaster);
        sambaConfig.setSecurityComboBox(cbSecurity);
        sambaConfig.setMapToGuestComboBox(cbMapToGuest);

        sambaConfig.setCommentTextField(tfComment);
        sambaConfig.setPathTextField(tfPath);
        sambaConfig.setCreateModeTextField(tfCreateMode);
        sambaConfig.setDirectoryModeTextField(tfDirectoryMode);
        sambaConfig.setBrowsableCheckBox(chbBrowseable);
        sambaConfig.setWritablecheckBox(chbWritable);
        sambaConfig.setGuestOkCheckBox(chbGuestOk);
        sambaConfig.setReadOnlyCheckBox(chbReadOnly);

        sambaConfig.setCommentTextField1(tfComment1);
        sambaConfig.setPathTextField1(tfPath1);
        sambaConfig.setCreateModeTextField1(tfCreateMode1);
        sambaConfig.setDirectoryModeTextField1(tfDirectoryMode1);
        sambaConfig.setBrowsableCheckBox1(chbBrowseable1);
        sambaConfig.setWritablecheckBox1(chbWritable1);
        sambaConfig.setGuestOkCheckBox1(chBGuestOk1);
        sambaConfig.setReadOnlyCheckBox1(chbReadOnly1);

        sambaConfig.setCommentTextField2(tfComment2);
        sambaConfig.setPathTextField2(tfPath2);
        sambaConfig.setCreateModeTextField2(tfCreateMode2);
        sambaConfig.setDirectoryModeTextField2(tfDirectoryMode2);
        sambaConfig.setBrowsableCheckBox2(chbBrowseable2);
        sambaConfig.setWritablecheckBox2(chbWritable2);
        sambaConfig.setGuestOkCheckBox2(chBGuestOk2);
        sambaConfig.setReadOnlyCheckBox2(chbReadOnly2);

        sambaConfig.setCommentTextField3(tfComment3);
        sambaConfig.setPathTextField3(tfPath3);
        sambaConfig.setCreateModeTextField3(tfCreateMode3);
        sambaConfig.setDirectoryModeTextField3(tfDirectoryMode3);
        sambaConfig.setBrowsableCheckBox3(chbBrowseable3);
        sambaConfig.setWritablecheckBox3(chbWritable3);
        sambaConfig.setGuestOkCheckBox3(chBGuestOk3);
        sambaConfig.setReadOnlyCheckBox3(chbReadOnly3);

        sambaConfig.openFile();
    }
}

/*##^## Designer {
    D{i:10;invisible:true}D{i:33;invisible:true}D{i:48;invisible:true}D{i:9;invisible:true}
}
 ##^##*/
