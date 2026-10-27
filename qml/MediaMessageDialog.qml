import QtQuick 2.9

Item {
    id: root

    property string title
    property string text
    property string icon: ""
    property string standardButtons: ""

    signal buttonClicked()
    signal yes()
    signal no()

    visible: false

    Loader {
        id: implementation
        anchors.fill: parent
        source: qtMajorVersion === 6
                ? "qrc:/MediaMessageDialogQt6.qml"
                : "qrc:/MediaMessageDialogQt5.qml"

        onLoaded: {
            item.title = root.title
            item.text = root.text
            item.icon = root.icon
            item.standardButtons = root.standardButtons
            if (root.visible)
                item.open()
        }
    }

    Connections {
        target: implementation.item

        function onButtonClicked() {
            root.visible = false
            root.buttonClicked()
        }

        function onYes() {
            root.yes()
        }

        function onNo() {
            root.no()
        }
    }

    onTitleChanged: if (implementation.item) implementation.item.title = title
    onTextChanged: if (implementation.item) implementation.item.text = text
    onIconChanged: if (implementation.item) implementation.item.icon = icon
    onStandardButtonsChanged: if (implementation.item) implementation.item.standardButtons = standardButtons

    onVisibleChanged: {
        if (!implementation.item)
            return
        if (visible)
            implementation.item.open()
        else
            implementation.item.close()
    }

    function open() {
        visible = true
    }

    function close() {
        visible = false
    }

    function setVisible(value) {
        visible = value
    }
}
