import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3
import AlarmViewLib 1.0

Rectangle{

    id: alarmDialog
    visible: true
    width: 800
    height: 440


    AlarmView
    {
        id:alarmView
    }

    BusyIndicator
    {
        id: busyIndication
        anchors.centerIn: mainRectangle
        running: false
    }

    RowLayout {
        spacing: 80
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        GroupBox {
            id: groupBox
            bottomPadding: 20
            rightPadding: 60
            font.pointSize: 16
            Layout.preferredHeight: 150
            Layout.preferredWidth: 250
            title: qsTr("Wyłącz Alarm")
            topPadding: 50
            leftPadding: 60
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            GridLayout {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                rows: 1

                columns: 1
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop

                Button {
                    id: picturePathButton
                    text: qsTr("WYŁĄCZ")
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    font.pointSize: 11
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    Layout.preferredWidth: 60
                    onClicked:
                    {
                        alarmView.stopAlarm()
                    }
                }
            }
        }

        GroupBox {
            id: groupBox1
            x: 375
            y: -1
            font.pointSize: 16
            GridLayout {
                anchors.left: parent.left
                rows: 2
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                columns: 2
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                anchors.top: parent.top

                Button {
                    id: picturePathButton1
                    text: qsTr("SNOOZE")
                    Layout.preferredWidth: 60
                    font.pointSize: 25
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    onClicked:
                    {
                        busyIndication.running=true
                        alarmView.snooze()
                        busyIndication.running=false
                    }
                }
            }
            title: qsTr("Drzemka")
            topPadding: 45
            Layout.preferredWidth: 350
            Layout.preferredHeight: 250
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            leftPadding: 50
        }

    }

    Component.onCompleted:
    {

    }
}


