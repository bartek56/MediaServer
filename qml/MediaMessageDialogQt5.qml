import QtQuick 2.9
import QtQuick.Dialogs 1.1

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
        icon: root.icon === "warning" ? StandardIcon.Warning : StandardIcon.Question
        standardButtons: root.standardButtons === "close"
                         ? StandardButton.Close
                         : root.standardButtons === "yesno"
                           ? StandardButton.Yes | StandardButton.No
                           : 0

        onButtonClicked: {
            root.buttonClicked()
            if (button === StandardButton.Yes)
                root.yes()
            else if (button === StandardButton.No)
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
