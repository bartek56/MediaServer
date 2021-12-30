import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Layouts 1.3
import AlarmConfigLib 1.0

Dialog
{
    id: alarmConfigDialog
    visible: true
    width: parent.width
    height: parent.height - 40
    topMargin: 40
    margins: 0
    padding: 1
    modal: true

    AlarmConfig
    {
        id: alarmConfig
    }

    Loader {
        anchors.fill:parent
        source:"screensavermanager.qml";
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        GridLayout {
            width: 470
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 470
            rowSpacing: 10
            rows: 4
            columns: 5
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop


            Text {
                id: timeText
                text: qsTr("Time [hh:mm]")
                font.pixelSize: 16
            }

            SpinBox {
                id: timeHHSpinBox
                width: 138
                value: 6
                spacing: 3
                from: 0
                to: 24
                Layout.columnSpan: 2
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                font.pointSize: 11
             }

             SpinBox {
                 id: timeMMSpinBox
                 width: 138
                 editable: false
                 Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                 spacing: 3
                 value: 35
                 font.pointSize: 11
                 to: 59
                 Layout.columnSpan: 2
                 from: 0
             }


             RadioButton {
                 id: newestSongsRadioButton
                 text: qsTr("The newest songs")
                 font.pointSize: 12
                 font.family: "Verdana"
                 Layout.columnSpan: 5
             }

             RadioButton {
                 id: playlistRadioButton
                 text: qsTr("Playlist")
                 font.pointSize: 12
                 bottomPadding: 27
                 Layout.columnSpan: 1
             }

             ComboBox {
                 id: playlistComboBox
                 Layout.preferredWidth: 200
                 Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
                 Layout.columnSpan: 4
             }

             CheckBox {
                 id: monCheckBox
                 width: 80
                 text: qsTr("Mon")
                 checked: false
                 Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                 font.family: "Times New Roman"
                 focusPolicy: Qt.NoFocus
             }

             CheckBox {
                 id: wedCheckBox
                 width: 80
                 text: qsTr("Wed")
                 checked: false
             }


             CheckBox {
                 id: friCheckBox
                 width: 80
                 text: qsTr("Fri")
                 checked: false
                 Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
             }

             CheckBox {
                 id: satCheckBox
                 x: 390
                 width: 80
                 text: qsTr("Sat")
                 focusPolicy: Qt.WheelFocus
                 checked: false
                 Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                 Layout.columnSpan: 2
             }

             CheckBox {
                 id: tueCheckBox
                 x: 22
                 width: 80
                 text: qsTr("Tue")
                 checked: false
                 Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
             }

             CheckBox {
                 id: thuCheckBox
                 x: 129
                 width: 80
                 text: qsTr("Thu")
                 Layout.columnSpan: 2
                 checked: false
              }


              CheckBox {
                   id: sunCheckBox
                   x: 390
                   width: 80
                   text: qsTr("Sun")
                   checked: false
                   Layout.columnSpan: 2
                   Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
               }


               Button {
                    id: button
                    text: qsTr("Test")
                    font.pointSize: 14
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.columnSpan: 2
                    onClicked: {
                        if(text === "Test")
                        {
                            text="Stop"
                            alarmConfig.bStartTestAlarm_onClicked()
                        }
                        else
                        {
                            text="Test"
                            alarmConfig.bStopTestAlarm_onClicked()
                        }

                    }
                }

                Switch {
                    id: enableAlarmSwitch
                    text: qsTr("Enable")
                    font.pointSize: 16
                    topPadding: 25
                    autoExclusive: false
                    checked: false
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    Layout.columnSpan: 3
                    onClicked: {
                        alarmConfig.switchEnableAlarm_onClicked(enableAlarmSwitch.checked)
                    }
               }

           }

        GridLayout {
            width: 250
            Layout.preferredWidth: 300
            rowSpacing: 25
            rows: 3
            columns: 2
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop


            Text {
                id: minVolumeText
                text: qsTr("Min Volume [%]")
                font.pixelSize: 16
            }

            SpinBox {
                id: minVolumeSpinBox
                to: 40
                from: 5
                value: 25
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillHeight: false
            }

            Text {
                id: maxVolumeText
                text: qsTr("Max Volume [%]")
                font.pixelSize: 16
            }

            SpinBox {
                id: maxVolumeSpinBox
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillHeight: false
                value: 70
                to: 100
                from: 50
            }

            Text {
                id: defaultVolumeText
                text: qsTr("Default Volume [%]")
                font.pixelSize: 16
            }

            SpinBox {
                id: defaultVolumeSpinBox
                to: 60
                from: 5
                Layout.fillHeight: false
                value: 30
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            }

            Text {
                id: growingVolumeText
                text: qsTr("Growing Volume [%]")
                font.pixelSize: 16
            }

            SpinBox {
                id: growingVolumeSpinBox
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.fillHeight: false
                value: 10
                to: 20
                from: 2
            }

            Text {
                id: growingSpeedText
                text: qsTr("Growing Speed [s]")
                font.pixelSize: 16
            }

            SpinBox {
                id: growingSpeedSpinBox
                value: 20
                from: 2
                Layout.fillHeight: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                to: 59
            }
        RowLayout{
           id: rowLayout
           Layout.columnSpan: 2

           Button
           {
                id:saveAlarmButton
                x: 559
                y: 380
                width: 100
                height: 40
                text: "save"
                onClicked:
                {
                    alarmConfig.bSaveAlarm_onClicked(minVolumeSpinBox.value, maxVolumeSpinBox.value, defaultVolumeSpinBox.value, growingVolumeSpinBox.value, growingSpeedSpinBox.value, newestSongsRadioButton.checked, playlistComboBox.currentText)
                    alarmConfig.bSaveAlarmService_onClicked(monCheckBox.checked, tueCheckBox.checked, wedCheckBox.checked, thuCheckBox.checked,friCheckBox.checked, satCheckBox.checked, sunCheckBox.checked, timeHHSpinBox.value, timeMMSpinBox.value)
                }
                onPressed: { busyAlarmConfig.running=true }
                onReleased:{ busyAlarmConfig.running=false }
            }
           Button
            {
                id: closeButton
                text: "Close"
                width: 160
                height: 40
                onClicked:
                {
                    alarmConfigDialog.close()
                }
            }
       }


        }

   }

   BusyIndicator
   {
       id: busyAlarmConfig
       anchors.centerIn: parent
       height: 100
       width: 100
       running: false
   }


    Component.onCompleted:
    {
        alarmConfig.loadAlarmConfigurations(minVolumeSpinBox, maxVolumeSpinBox, defaultVolumeSpinBox, growingVolumeSpinBox, growingSpeedSpinBox, newestSongsRadioButton, playlistRadioButton, playlistComboBox)
        alarmConfig.loadAlarmService(monCheckBox, tueCheckBox, wedCheckBox, thuCheckBox,friCheckBox, satCheckBox, sunCheckBox, timeHHSpinBox, timeMMSpinBox)
        alarmConfig.checkAlarmService(enableAlarmSwitch)
    }
}


