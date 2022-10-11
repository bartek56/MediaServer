import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.2
import ScreenSaverLib 1.0

Dialog
{
    id: screenSaverDialog
    visible: true
    modal: true
    width: parent.width
    height: parent.height

    property int i: 0
    property bool isRandom: false
    property int totalFileCount: folderModel.count


    ScreenSaverView{
        id: screenSaver
    }

    Rectangle{
        height: parent.height+25
        width: parent.width+25
        x:parent.x-25
        y:parent.y-25
        color: "black"
    }

    MouseArea{
        height: parent.height
        width: parent.width
        onClicked:
        {
            timer.stop()
            screenSaver.exit()
            screenSaverDialog.visible=false
        }
    }

    FolderListModel {
        id: folderModel
        nameFilters: ["*.jpg"]
    }

    onTotalFileCountChanged: {
        timer.triggeredOnStart = true
        timer.start()
    }

    Image {
        id: image
        width: screenSaverDialog.width
        height: (9/16)*screenSaverDialog.width
        anchors.verticalCenter: parent.verticalCenter
        x: parent.x-25
    }

    Timer {
        id:timer
        repeat: true;
        onTriggered:
        {
            console.log(folderModel.count)
            console.log(Math.ceil(Math.random()*folderModel.count))

            if(isRandom)
            {
                image.source = folderModel.folder +"/"+ folderModel.get( Math.ceil(Math.random()*folderModel.count),"fileBaseName")
            }
            else
            {
                if (++i == folderModel.count) i = 0
                image.source = folderModel.folder + "/" + folderModel.get(i,"fileBaseName")
            }
        }
    }

    Component.onCompleted:
    {
        screenSaver.init(timer, folderModel, screenSaverDialog);
    }
}
