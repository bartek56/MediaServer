import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import YoutubeLib 1.0

Rectangle
{
    id: mainRectangle

    Youtubedl
    {
        id:youtubedl
    }

    ScrollView
    {
        id:scroll
        anchors.fill: parent

        ListView
        {
            id: listView
            anchors.fill: parent
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
            width: mainRectangle.width

            Column
            {
                spacing: -20

                TextArea
                {
                    height: 40
                    width: wrapper.width
                    font.family: "Helvetica"
                    readOnly: true
                    font.pointSize: 16
                    text: dataObject.name
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                }

                Flickable
                {
                    id: flickable
                    width: wrapper.width
                    height: 40

                    TextArea.flickable: TextArea
                    {
                        id: linkText
                        readOnly: true
                        //fontSizeMode: Text.Fit
                        text:dataObject.link
                        color: wrapper.ListView.isCurrentItem ? "red" : "black"
                        wrapMode:TextArea.Wrap
                    }
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

    Component.onCompleted:
    {
        youtubedl.loadPlaylists()
    }
}
