import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

ToolBar{
    id: toolBar

    Label{
        height: 20
        text: "Clock"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        transformOrigin: Item.Center
    }
}
