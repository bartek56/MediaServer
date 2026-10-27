import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import AlarmViewLib 1.0

Rectangle {
    id: alarmDialog
    visible: true
    width: 800
    height: 480
    color: "#101522"
    property var currentDate: new Date()
    property var weekdays: ["niedziela", "poniedziałek", "wtorek", "środa", "czwartek", "piątek", "sobota"]

    function twoDigits(value) {
        return value < 10 ? "0" + value : value
    }

    AlarmView { id: alarmView }

    Component.onCompleted: alarmView.refreshCurrentSong()

    Timer {
        interval: 5000
        repeat: true
        running: true
        onTriggered: alarmView.refreshCurrentSong()
    }

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: alarmDialog.currentDate = new Date()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 28
        spacing: 0

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 14

            Text {
                text: "⏰"
                color: "#FFFFFF"
                font.pixelSize: 50
            }

            Text {
                text: alarmView.alarmTime
                color: "#FFFFFF"
                font.pixelSize: 58
                font.bold: true
            }
        }

        Text {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10
            text: qsTr("ODŁÓŻ ALARM")
            color: "#AEBBD0"
            font.pixelSize: 18
            font.bold: true
            font.letterSpacing: 2
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 18
            spacing: 16

            Repeater {
                model: [qsTr("+5 min"), qsTr("+10 min"), qsTr("+15 min")]

                delegate: Button {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 105
                    text: modelData
                    font.pixelSize: 27
                    font.bold: true

                    background: Rectangle {
                        radius: 16
                        color: parent.pressed ? "#356AC7" : "#4F8CFF"
                    }

                    onClicked: {
                        if(index === 0) alarmView.snooze5min()
                        else if(index === 1) alarmView.snooze10min()
                        else alarmView.snooze15min()
                        Qt.callLater(Qt.quit)
                    }
                }
            }
        }

        Item { Layout.fillHeight: true }

        Text {
            Layout.fillWidth: true
            text: "♫  " + alarmView.currentSong
            color: "#D7E0EF"
            font.pixelSize: 22
            elide: Text.ElideMiddle
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 18
            Layout.preferredWidth: 340
            Layout.preferredHeight: 64
            text: qsTr("Zatrzymaj alarm")
            font.pixelSize: 21
            flat: true

            background: Rectangle {
                radius: 32
                color: parent.pressed ? "#6C3D48" : "#482D38"
                border.color: "#92606D"
                border.width: 1
            }

            contentItem: Text {
                text: parent.text
                color: "#E8B8C2"
                font: parent.font
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: confirmation.visible = true
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.topMargin: 14

            Text {
                Layout.fillWidth: true
                text: alarmDialog.weekdays[alarmDialog.currentDate.getDay()] +
                      ", " + alarmDialog.twoDigits(alarmDialog.currentDate.getDate()) +
                      "." + alarmDialog.twoDigits(alarmDialog.currentDate.getMonth() + 1) +
                      "." + alarmDialog.currentDate.getFullYear()
                color: "#8291A8"
                font.pixelSize: 16
            }

            Text {
                text: alarmDialog.twoDigits(alarmDialog.currentDate.getHours()) +
                      ":" + alarmDialog.twoDigits(alarmDialog.currentDate.getMinutes()) +
                      ":" + alarmDialog.twoDigits(alarmDialog.currentDate.getSeconds())
                color: "#D7E0EF"
                font.pixelSize: 18
                font.bold: true
            }
        }
    }

    Rectangle {
        id: confirmation
        anchors.fill: parent
        visible: false
        color: "#B8101522"

        Rectangle {
            anchors.centerIn: parent
            width: 390
            height: 210
            radius: 18
            color: "#1C2638"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 24
                spacing: 10

                Text {
                    Layout.alignment: Qt.AlignHCenter
                    text: qsTr("Zatrzymać alarm?")
                    color: "#FFFFFF"
                    font.pixelSize: 25
                    font.bold: true
                }

                Text {
                    Layout.fillWidth: true
                    text: qsTr("Upewnij się, że już nie śpisz.")
                    color: "#B9C5D8"
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignHCenter
                }

                Item { Layout.fillHeight: true }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    Button {
                        Layout.fillWidth: true
                        text: qsTr("Anuluj")
                        onClicked: confirmation.visible = false
                    }

                    Button {
                        Layout.fillWidth: true
                        text: qsTr("Zatrzymaj")
                        onClicked: {
                            alarmView.stopAlarm()
                            Qt.callLater(Qt.quit)
                        }
                    }
                }
            }
        }
    }
}
