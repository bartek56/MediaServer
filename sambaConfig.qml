import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.VirtualKeyboard 2.1
import "content"

Dialog {
    id:dialog
    visible: true
    width: 800
    height: 440
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    //standardButtons: Dialog.Save | Dialog.RestoreDefaults | Dialog.Cancel

    footer: DialogButtonBox
    {

        Button{
             text: "Save"
             onClicked:
             {
                g_mainWindow.bSave_onClicked(tfWorkgroup.getText(0,tfWorkgroup.length))
             }
         }

       Button{
            text: "Close"
            onClicked:
            {
                dialog.close()
            }
       }
    }

    TextField {
        id: tfWorkgroup
        x: 226
        y: 81
        width: 158
        height: 40
        text: qsTr("WORKGROUP")
        placeholderText: "One line field"
        //enterKeyAction: EnterKeyAction.Next
        onAccepted: passwordField.focus = true
    }

    Text {
        id: lWorkgroup
        x: 66
        y: 81
        width: 132
        height: 40
        text: qsTr("Workgroup")
        font.pixelSize: 21
    }
    MouseArea {
        anchors.fill: parent
        visible: handwritingInputPanelActive
    }
}
