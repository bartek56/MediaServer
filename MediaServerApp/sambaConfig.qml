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


    TextField
    {
        id: tfWorkgroup
        x: 226
        y: 81
        width: 158
        height: 40
        text: qsTr("WORKGROUP")
        placeholderText: "One line field"
    }

    Text
    {
        id: lWorkgroup
        x: 66
        y: 81
        width: 132
        height: 40
        text: qsTr("Workgroup")
        font.pixelSize: 21
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
                width: 160
                height: 40
                onClicked:
                {
                    dialog.close()
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
}

