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
        id:sambaConfig
    }

    TabBar {
        id: tabBar
        width: parent.width
        TabButton {
            text: qsTr("Home")
        }
        TabButton {
            text: qsTr("Discover")
        }
        TabButton {
            text: qsTr("Activity")
        }
    }

    StackLayout {
        width: parent.width
        currentIndex: tabBar.currentIndex
        Item {
            id: homeTab

            GridLayout {
                id: gridLayout
                x: 0
                y: 46
                width: 446
                height: 323
                rows: 5
                columns: 2

                Text
                {
                    id: lWorkgroup
                    width: 132
                    height: 40
                    text: qsTr("workgroup")
                    font.pixelSize: 21
                }

                TextField
                {
                    id: tfWorkgroup
                    width: 158
                    height: 40
                    placeholderText: "WORKGROUP"
                }

                Text
                {
                    id: lServerString

                    width: 132
                    height: 40
                    text: qsTr("server string")
                    font.pixelSize: 21
                }

                TextField
                {
                    id: tfServerString
                    width: 158
                    height: 40
                    placeholderText: "Server"
                }

                Text
                {
                    id: lNetbiosName
                    width: 132
                    height: 40
                    text: qsTr("netbios name")
                    font.pixelSize: 21
                }

                TextField
                {
                    id: tfNetbiosName
                    width: 158
                    height: 40
                    text: ""
                    placeholderText: "Server"
                }

                Text
                {
                    id: lSecurity
                    width: 132
                    height: 40
                    text: qsTr("security")
                    font.pixelSize: 21
                }

                ComboBox {
                    id: cbSecurity
                    model: ListModel {

                        ListElement {
                            key: "user"
                        }
                        ListElement {
                            key: "share"
                        }
                    }
                    textRole: "key"
                }

                Text
                {
                    id: lMapToGuest
                    width: 132
                    height: 40
                    text: qsTr("map to guest")
                    font.pixelSize: 21
                }

                ComboBox {
                    id: cbMapToGuest
                    textRole: "key"
                    model: ListModel {
                        ListElement { key: "Bad User"; }
                        ListElement { key: "Bad Password";}
                        ListElement { key: "Never";}
                    }
                }
            }

            GridLayout {
                id: gridLayout1
                x: 531
                y: 62
                width: 192
                height: 292
                columns: 1

                CheckBox {
                    id: cbBrowseable
                    text: qsTr("browseable")
                    checkable: true
                }

                CheckBox {
                    id: cbLocalMaster
                    text: qsTr("local master")
                    checkable: true
                }

                CheckBox {
                    id: cbDomainMaster
                    text: qsTr("domain master")
                    checkable: true
                }
            }
        }
        Item {
            id: discoverTab
        }
        Item {
            id: activityTab
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
                tfServerString.text="Server"
                tfNetbiosName.text="Server"
                cbBrowseable.checked=true
                cbLocalMaster.checked=true
                cbDomainMaster.checked=true
                cbSecurity.currentIndex=0
                cbMapToGuest.currentIndex=0
            }
        }

        Button
        {
            width: 160
            height: 40
            text: "Save"
            onClicked:
            {
                sambaConfig.bSave_onClicked(tfWorkgroup.getText(0,tfWorkgroup.length));
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
        sambaConfig.setBrowsableCheckBox(cbBrowseable);
        sambaConfig.setLocalMastercheckBox(cbLocalMaster);
        sambaConfig.setDomainMasterCheckBox(cbDomainMaster);
        sambaConfig.setSecurityComboBox(cbSecurity);
        sambaConfig.setMapToGuestComboBox(cbMapToGuest);
        sambaConfig.openFile();
    }
}

