import QtQuick 2.0
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.2
import ScreenSaverLib 1.0

Dialog
{
    id: screenSaverDialog
    visible: true
    modal: true

    width: 800
    height: 480

    property int i: 0
    property bool isRandom: true
    property int sleep: 2
    property string path: "/home/bartosz/Pictures/tapety"

    ScreenSaver{
        id: screenSaver
    }

    MouseArea{
        height: parent.height
        width: parent.width
        onClicked:
        {
            screenSaverDialog.visible=false
            screenSaver.exit()
        }
    }

    FolderListModel {
        id: folderModel
        nameFilters: ["*.jpg"]
        folder: "file:" + path
    }

    Image {
        id: image
        width: parent.width
        height: parent.height
    }

    Timer {
        id:timer
        interval: sleep*1000;
        running: true;
        repeat: true;
        triggeredOnStart: true;
        onTriggered:
        {
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
        screenSaver.init();
    }
}
