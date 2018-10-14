import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

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
         }

       Button{
            text: "Close"
            onClicked:
            {
                dialog.close()
            }
        }


    }
}
