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

    GridLayout {
        x: 20
        y: 20
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        rows: 2

        columns: 2
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop

        ToolButton {
            id: toolButtonSnooze5min
            font.wordSpacing: 1
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredHeight: 100
            Layout.preferredWidth: 170
            leftPadding: 6

            Text {
                id: snooze5minText

                width: 50
                height: 26
                text: qsTr("SNOOZE 5min")
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                font.letterSpacing: 1
                anchors.horizontalCenterOffset: 0
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 22
            }

            onClicked:
            {
                alarmView.snooze5min()
            }
            onPressed: { busyAlarm.running=true }
            onReleased:{ busyAlarm.running=false }
        }

        ToolButton {
            id: toolButtonSnooze10min
            Layout.preferredHeight: 140
            font.wordSpacing: 1
            leftPadding: 6
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: 240
            Text {
                id: snooze10minText
                width: 50
                height: 26
                text: qsTr("SNOOZE 10min")
                font.bold: true
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 22
                horizontalAlignment: Text.AlignHCenter
                font.letterSpacing: 1
                verticalAlignment: Text.AlignVCenter
                wrapMode: Text.WordWrap
            }
            onClicked:
            {
                alarmView.snooze10min()
            }
            onPressed: { busyAlarm.running=true }
            onReleased:{ busyAlarm.running=false }

        }

        ToolButton {
            id: toolButtonShutdown
            Layout.preferredHeight: 100
            font.wordSpacing: 1
            leftPadding: 6
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: 170
            Text {
                id: shutdownAlarmText
                width: 50
                height: 26
                text: qsTr("SHUT DOWN")
                anchors.verticalCenter: parent.verticalCenter
                font.bold: true
                font.pointSize: 22
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                font.letterSpacing: 1
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenterOffset: 0
                wrapMode: Text.WordWrap
            }
            onClicked:
            {
                alarmView.stopAlarm()
            }
            onPressed: { busyAlarm.running=true }
            onReleased:{ busyAlarm.running=false }

        }

        ToolButton {
            id: toolButtonSnooze15min
            Layout.preferredHeight: 100
            font.wordSpacing: 1
            leftPadding: 6
            font.letterSpacing: 1
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: 170
            Text {
                id: snooze15minText
                width: 50
                height: 26
                text: qsTr("SNOOZE 15min")
                font.pointSize: 22
                anchors.horizontalCenter: parent.horizontalCenter
                horizontalAlignment: Text.AlignHCenter
                font.letterSpacing: 1
                verticalAlignment: Text.AlignVCenter
                anchors.horizontalCenterOffset: 0
                wrapMode: Text.WordWrap
                anchors.verticalCenter: parent.verticalCenter
            }
            onClicked:
            {
                alarmView.snooze15min()
            }
            onPressed: { busyAlarm.running=true }
            onReleased:{ busyAlarm.running=false }
        }
    }

    BusyIndicator
    {
        id: busyAlarm
        anchors.centerIn: parent
        height: 100
        width: 100
        running: false
    }

    Component.onCompleted:
    {

    }
}


