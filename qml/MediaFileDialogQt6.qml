import QtQuick
import QtQuick.Dialogs

Item {
    id: root

    property bool selectFolder: false
    property url folder
    property url fileUrl

    signal accepted()
    signal rejected()

    FolderDialog {
        id: folderDialog
        currentFolder: root.folder

        onAccepted: {
            root.folder = selectedFolder
            root.accepted()
        }

        onRejected: root.rejected()
    }

    FileDialog {
        id: fileDialog
        currentFolder: root.folder
        fileMode: FileDialog.OpenFile

        onAccepted: {
            root.folder = currentFolder
            root.fileUrl = selectedFile
            root.accepted()
        }

        onRejected: root.rejected()
    }

    function open() {
        if (root.selectFolder)
            folderDialog.open()
        else
            fileDialog.open()
    }

    function close() {
        folderDialog.close()
        fileDialog.close()
    }
}
