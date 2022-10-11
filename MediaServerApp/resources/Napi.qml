import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.1
import NapiManagerLib 1.0


Dialog
{
    id: napiDialog
    visible: true
    width: parent.width
    height: parent.height - 40
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    property string videoPath: "file:///mnt/"

    NapiManagerView
    {
        id:napiManager
    }

    Loader {
        anchors.fill:parent
        source:"ScreenSaverManager.qml";
    }

    FileDialog {
        id: movieFileDialog
        folder: videoPath
        width: parent.width
        height: parent.height
        selectFolder: false
        onAccepted:
        {
            var folderPath = movieFileDialog.folder;
            var fileUrl = movieFileDialog.fileUrl;
            var fileName = fileUrl.toString().replace(folderPath+"/","");
            movieTitleTextField.text = fileName;

            napiManager.bNapiFileDialog_onAccepted(folderPath, fileName);
            napiDialog.visible=true;
        }
        onRejected:
        {
            napiDialog.visible=true;
        }
    }

    GridLayout {
        x: 38
        y: 51
        width: 610
        height: 296
        rows: 3
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 3

        Text {
            id: movieText
            text: qsTr("Movie")
            Layout.preferredWidth: 70
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 22
        }

        TextField {
            id: movieTitleTextField
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            enabled: false
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            id: bOpenFileDialog
            text: qsTr("Open")
            onClicked:
            {
                infoText.text="";
                movieFileDialog.open()
                napiDialog.visible=false
            }
        }

        Text {
            id: element
            text: qsTr("Language")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            Layout.columnSpan: 3
            font.pixelSize: 23
        }

        ColumnLayout {
            id: columnLayout
            width: 100
            height: 100
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            Layout.columnSpan: 3

            RadioButton {
                id: englishRadioButton
                text: qsTr("English")
                onClicked:
                {
                    napiManager.rbEnglish_onClicked()
                    infoText.text="";
                }
            }

            RadioButton {
                id: polishRadioButton
                text: qsTr("Polish")
                onClicked:
                {
                    napiManager.rbPolish_onClicked()
                    infoText.text="";
                }
            }
        }

        Text {
            id: infoText
            text: qsTr("")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.columnSpan: 3
            font.pixelSize: 28
        }
    }
    RowLayout
    {
        id: rowLayout
        anchors.bottom: parent.bottom

        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter


        Button {
            id: bDownload
            x: 480
            y: 370
            height: 40
            text: "Download"
            onClicked:
            {
                if(movieTitleTextField.text.length>1)
                {
                    napiManager.bDownload_onClicked(infoText)
                }
                else
                {
                    infoText.text="Path to movie is empty";
                }
            }
            onPressed: { busyNapi.running=true }
            onReleased:{ busyNapi.running=false }

        }

        Button
        {
            id: bExit
            x: 600
            y: 370
            text: "Exit"
            height: 40
            onClicked:
            {
                napiDialog.close()
            }
        }

    }
    BusyIndicator
    {
        id: busyNapi
        anchors.centerIn: parent
        height: 100
        width: 100
        running: false
    }

    Component.onCompleted:
    {
        napiManager.setVideoPath(napiDialog)
        napiManager.init(englishRadioButton, polishRadioButton)
    }
}
