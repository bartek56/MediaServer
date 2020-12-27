import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import YoutubeLib 1.0

Rectangle
{
    id: root
    visible: true
    color: "gray"
    border.color: Qt.lighter(color)
    z: -1

    property int xPosition: 0
    property int xPolicy: ScrollBar.AlwaysOn
    property int yPolicy: ScrollBar.AlwaysOn
    property int xSizePreferred: 1024
    property int ySizePreferred: 768
    property int xSizeActual: 0
    property int ySizeActual: 0
    property int xSizeMobile: xSizePreferred/2
    property int ySizeMobile: ySizePreferred*2-header.height

    property int rightFrameXPosition: xSizePreferred/2
    property int rightFrameYPosition: header.height


    onWidthChanged:
    {
        if(root.width > xSizePreferred)
        {
            xSizeActual=xSizePreferred
            ySizeActual=ySizePreferred

            xPolicy = ScrollBar.AlwaysOff
            xPosition = (root.width-xSizeActual)/2

            rightFrameXPosition=xSizePreferred/2
            rightFrameYPosition=header.height
        }
        else if(root.width < xSizePreferred && root.width>xSizeMobile)
        {
            ySizeActual=ySizeMobile
            xSizeActual=xSizeMobile

            xPolicy = ScrollBar.AlwaysOff
            xPosition = (root.width-xSizeActual)/2

            rightFrameXPosition=0
            rightFrameYPosition=header.height+leftFrame.height
        }
        else
        {
            ySizeActual=ySizeMobile
            xSizeActual=xSizeMobile

            xPosition = 0;
            xPolicy = ScrollBar.AlwaysOn

            rightFrameXPosition=0
            rightFrameYPosition=header.height+leftFrame.height
        }
    }

    onHeightChanged:
    {
        if(root.height > ySizePreferred)
        {
            yPolicy = ScrollBar.AlwaysOff
        }
        else
        {
            yPolicy = ScrollBar.AlwaysOn
        }
    }


    Flickable
    {
        anchors.fill: parent
        contentWidth: xSizeActual
        contentHeight: ySizeActual

        Rectangle
        {
            id: mainFrame
            width: xSizeActual
            height: ySizeActual

            clip: true
            color: "red"
            border.color: Qt.lighter(color)
            x: xPosition
            y: 0

            Rectangle
            {
                id: header
                anchors.top: mainFrame.top
                anchors.right: mainFrame.right
                anchors.left: mainFrame.left
                height: 70
                color: "orange"
                border.color: Qt.lighter(color)
                Text
                {
                    anchors.centerIn: parent
                    text: "header"
                }
            }

            Rectangle
            {
                id: leftFrame
                x: 0
                y: header.height
                width: xSizePreferred/2
                height: ySizePreferred-header.height
                color: "gold"
                border.color: Qt.lighter(color)
                Text
                {
                    anchors.centerIn: parent
                    text: "left Frame"
                }
            }

            Rectangle
            {
                id: rightFrame
                x: rightFrameXPosition
                y: rightFrameYPosition
                width: xSizePreferred/2
                height: ySizePreferred-header.height
                color: "olive"
                border.color: Qt.lighter(color)
                Text
                {
                    anchors.centerIn: parent
                    text: "right Frame"
                }
            }
        }
        ScrollBar.horizontal: ScrollBar { id: hbar; height: 12; active: vbar.active; policy: xPolicy}
        ScrollBar.vertical: ScrollBar { id: vbar; width: 12; active: hbar.active; policy: yPolicy }
    }
}
