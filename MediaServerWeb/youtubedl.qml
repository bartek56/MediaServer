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
                border.color: Qt.lighter("blue")

                Column{
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
                            id: playlistTextField
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
                            id: linkTextField
                            height: 30
                            Layout.alignment: Qt.AlignCenter

                            text: "https://youtube"
                        }

                        Button
                        {
                            Layout.column: 0
                            Layout.row: 3
                            Layout.alignment: Qt.AlignRight
                            text:"remove"
                            onClicked:
                            {
                                youtubedl.removePlaylist(playlistTextField.text)
                            }
                        }

                        Button
                        {
                            text:"add/update"
                            Layout.column: 1
                            Layout.row: 3
                            Layout.alignment: Qt.AlignLeft
                            onClicked:
                            {
                                youtubedl.addNewPlaylist(playlistTextField.text, linkTextField.text)
                            }
                        }
                    }

                    ScrollView{
                        id:scrollList
                        width: leftFrame.width
                        height: 360
                        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                        ScrollBar.vertical.width: 12

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
                            height: 45
                            width: leftFrame.width-10
                            x: 5

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
                                    listView.currentIndex=index
                                    playlistTextField.text=dataObject.name
                                    linkTextField.text=dataObject.link
                                }
                            }
                        }
                    }

                    Column
                    {
                        Row
                        {
                            spacing: 10
                            x:20
                            Switch
                            {
                                id: autoStartupSwitch
                                text: qsTr("Auto Startup")
                                checked: false
                                font.pointSize: 10
                                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                                onClicked:
                                {
                                    youtubedl.autoStartupSwitch_OnClicked(autoStartupSwitch.checked)
                                }
                            }
                            Button
                            {
                                id: startDownloadButton
                                text:"start"
                                onClicked:
                                {
                                    youtubedl.startDownload(startDownloadButton)
                                }
                            }
                        }
                        Row
                        {
                            topPadding: 20
                            spacing: 20
                            x:260
                            Button
                            {
                                text:"reset"
                                onClicked:
                                {
                                    playlistsModel.clear()
                                    youtubedl.loadPlaylists()
                                }
                            }

                            Button
                            {
                                text:"apply"
                                onClicked:
                                {
                                    youtubedl.save()
                                }
                            }
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
                border.color: Qt.lighter("blue")
                Column
                {
                    anchors.fill: parent
                    topPadding: 20
                    Text
                    {
                        horizontalAlignment: Text.AlignHCenter
                        text: "Quick Download"
                        font.pixelSize: 26
                        anchors.horizontalCenter: parent.horizontalCenter
                        bottomPadding: 20
                    }

                    GridLayout
                    {
                        width: rightFrame.width
                        columns: 3
                        rowSpacing: 15

                        Label
                        {
                            Layout.alignment: Qt.AlignCenter
                            font.pixelSize: 20
                            text: "Link:"
                        }
                        TextField
                        {
                            id: quickdownloadLinkTextField
                            Layout.rightMargin: 10
                            Layout.alignment: Qt.AlignRight
                            Layout.preferredWidth:350
                            Layout.columnSpan: 2
                            text: "https://youtube.com"
                        }
                        RadioButton
                        {
                            id: video480p
                            Layout.alignment: Qt.AlignCenter
                            text:"Video 480p"
                        }
                        RadioButton
                        {
                            id: video720p
                            Layout.alignment: Qt.AlignCenter
                            text:"Video 720p"
                        }

                        RadioButton
                        {
                            id: video4k
                            Layout.alignment: Qt.AlignCenter
                            text:"Video 4K"
                        }
                        RadioButton
                        {
                            id: audio
                            Layout.alignment: Qt.AlignCenter
                            text:"Audio MP3"
                            checked: true
                            Layout.columnSpan: 3
                        }

                        Button
                        {
                            id:quickdownloadButton
                            Layout.columnSpan: 3
                            Layout.alignment: Qt.AlignCenter
                            text: "Download"
                            onClicked:
                            {
                                if(video4k.checked)
                                {
                                    youtubedl.download4K(quickdownloadLinkTextField.text, quickdownloadButton);
                                }
                                else if (video720p.checked)
                                {
                                    youtubedl.download720p(quickdownloadLinkTextField.text, quickdownloadButton);
                                }
                                else if (video480p.checked)
                                {
                                    youtubedl.download480p(quickdownloadLinkTextField.text, quickdownloadButton)
                                }
                                else if (audio.checked)
                                {
                                    youtubedl.downloadmp3(quickdownloadLinkTextField.text, quickdownloadButton);
                                }
                            }
                        }
                    }
                }
            }
        }
        ScrollBar.horizontal: ScrollBar { id: hbar; height: 12; active: vbar.active; policy: xPolicy}
        ScrollBar.vertical: ScrollBar { id: vbar; width: 12; active: hbar.active; policy: yPolicy }
    }
    Component.onCompleted:
    {
        youtubedl.loadPlaylists()
        youtubedl.checkStatus(autoStartupSwitch)
        playlistTextField.text=playlistsModel.get(0).name
        linkTextField.text=playlistsModel.get(0).link
    }
}

