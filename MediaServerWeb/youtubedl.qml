import QtQuick 2.8
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


    Youtubedl
    {
        id:youtubedl
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
                    font.pixelSize: 26
                    text: "Youtube downloader"
                }
            }

            Rectangle
            {
                id: leftFrame
                x: 0
                y: header.height
                width: xSizePreferred/2
                height: ySizePreferred-header.height


                Column{
                    id: column
                    anchors.fill: parent
                    spacing: 60
                    bottomPadding: 200
                    GridLayout
                    {

                        height: 100
                        anchors.right: parent.right
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        columns: 2
                        rows: 3


                        Label
                        {
                            height: 30
                            text: "PlayList Name"
                            verticalAlignment: Text.AlignVCenter
                        }
                        TextField
                        {
                            height: 30
                            text: "New Playlist"
                            Layout.alignment: Qt.AlignCenter

                        }
                        Label
                        {
                            text: "Link"
                            height: 30
                        }
                        TextField
                        {
                            height: 30
                            Layout.alignment: Qt.AlignCenter

                            text: "https://youtube"
                        }

                        Button
                        {
                            text:"add"
                            Layout.column: 1
                            Layout.row: 3
                            Layout.alignment: Qt.AlignCenter
                        }
                    }

                    ScrollView{
                        id:scrollList
                        width: leftFrame.width
                        height: 380

                        ListView
                        {
                            id: listView
                            anchors.fill: scrollList
                            model: playlistsModel
                            delegate: playlistsDelegate
                        }
                    }
                    Component
                    {
                        id: playlistsDelegate
                        Rectangle
                        {
                            id: wrapper
                            height: 60
                            width: leftFrame.width

                            Column
                            {
                                spacing: -20
                                TextArea
                                {
                                    height: 40
                                    width: wrapper.width
                                    font.family: "Helvetica"
                                    readOnly: true
                                    font.pointSize: 12
                                    text: dataObject.name
                                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                                }


                                TextArea
                                {
                                    id: linkText
                                    readOnly: true
                                    //fontSizeMode: Text.Fit
                                    text: dataObject.link
                                    font.pointSize: 8
                                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                                    wrapMode:TextArea.Wrap
                                }
                            }
                            MouseArea
                            {
                                anchors.fill: parent
                                onClicked:
                                {
                                    console.log(playlistsModel.get(index).name)
                                    console.log(dataObject.name)
                                    listView.currentIndex=index
                                }
                            }
                        }
                    }

                    Column{
                        Button
                        {
                            x:10
                            text:"remove"
                        }

                        Button
                        {
                            x:370
                            text:"apply"
                        }
                    }
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
    Component.onCompleted:
    {
        youtubedl.loadPlaylists()
    }
}

