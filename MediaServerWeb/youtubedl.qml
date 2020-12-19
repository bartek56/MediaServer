import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import YoutubeLib 1.0

Rectangle {
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
        id: myDelegate
        Item
        {
            id: wrapper
            width: 180
            height: 60
            Text {
                id: contactInfo
                text: dataObject.name + ": " + dataObject.link
                color: wrapper.ListView.isCurrentItem ? "red" : "black"
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    console.log(myModel.get(index).name)
                    console.log(dataObject.name)
                    listView.currentIndex=index
                }
            }
        }
    }
    ListView {
        id: listView
        anchors.fill: parent
        model: myModel
        delegate: myDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
    }
    Component.onCompleted:
    {
        youtubedl.test(listView)
    }
}
