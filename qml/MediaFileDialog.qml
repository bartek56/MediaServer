import QtQuick 2.9

Item {
    id: root

    property bool selectFolder: false
    property url folder
    property url fileUrl

    signal accepted()
    signal rejected()

    visible: false

    Loader {
        id: implementation
        anchors.fill: parent
        source: qtMajorVersion === 6
                ? "qrc:/MediaFileDialogQt6.qml"
                : "qrc:/MediaFileDialogQt5.qml"

        onLoaded: {
            item.folder = root.folder
            item.selectFolder = root.selectFolder
            item.width = root.width
            item.height = root.height
            if (root.visible)
                item.open()
        }
    }

    Connections {
        target: implementation.item

        function onAccepted() {
            root.folder = implementation.item.folder
            root.fileUrl = implementation.item.fileUrl
            root.visible = false
            root.accepted()
        }

        function onRejected() {
            root.visible = false
            root.rejected()
        }
    }

    onFolderChanged: if (implementation.item) implementation.item.folder = folder
    onSelectFolderChanged: if (implementation.item) implementation.item.selectFolder = selectFolder

    function open() {
        visible = true
        if (implementation.item)
            implementation.item.open()
    }

    function close() {
        visible = false
        if (implementation.item)
            implementation.item.close()
    }
}
