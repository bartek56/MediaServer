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

    ListView {
        id: listView
        anchors.fill: parent
        model: myModel
        delegate: Text { text: "Animal " + type + ", "+size}
    }
    Component.onCompleted:
    {
        console.log("start");
        youtubedl.test(listView)
    }
}
