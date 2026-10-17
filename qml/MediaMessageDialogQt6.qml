import QtQuick
import QtQuick.Dialogs

Item {
    id: root

    property string title
    property string text
    property string icon: ""
    property string standardButtons: ""

    signal buttonClicked()
    signal yes()
    signal no()

    MessageDialog {
        id: dialog
        title: root.title
        text: root.text
        buttons: root.standardButtons === "close"
                 ? MessageDialog.Close
                 : root.standardButtons === "yesno"
                   ? MessageDialog.Yes | MessageDialog.No
                   : 0

        onButtonClicked: function(button, role) {
            root.buttonClicked()
            if (button === MessageDialog.Yes)
                root.yes()
            else if (button === MessageDialog.No)
                root.no()
        }
    }

    function open() {
        dialog.open()
    }

    function close() {
        dialog.close()
    }
}
