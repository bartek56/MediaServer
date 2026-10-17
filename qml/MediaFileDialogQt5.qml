import QtQuick 2.9
import QtQuick.Dialogs 1.1

Item {
    id: root

    property bool selectFolder: false
    property url folder
    property url fileUrl

    signal accepted()
    signal rejected()

    FileDialog {
        id: dialog
        width: root.width
        height: root.height
        folder: root.folder
        selectFolder: root.selectFolder

        onAccepted: {
            root.folder = dialog.folder
            root.fileUrl = dialog.fileUrl
            root.accepted()
        }

        onRejected: root.rejected()
    }

    function open() {
        dialog.open()
    }

    function close() {
        dialog.close()
    }
}
