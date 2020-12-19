import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import YoutubeLib 1.0

Rectangle
{
    id: rectangle
    visible: true
    width: 800
    height: 440

    Youtubedl
    {
        id:youtubedl
    }

        Component
        {
            id: playlistsDelegate
            Item
            {
                id: wrapper
                width: 180
                height: 60

                Column
                {
                    Text
                    {
                        font.family: "Helvetica"
                        font.pointSize: 16
                        text: dataObject.name
                        color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    }
                    Text
                    {
                        text:dataObject.link
                        color: wrapper.ListView.isCurrentItem ? "red" : "black"

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
        ListView
        {
            id: listView
            anchors.fill: parent
            model: playlistsModel
            delegate: playlistsDelegate
        }


    Component.onCompleted:
    {
        youtubedl.loadPlaylists()
    }
}
