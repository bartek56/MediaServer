#ifndef ALARMVIEW_H
#define ALARMVIEW_H

#include <QObject>
#include "src/EditAlarmConfigFile.h"

class AlarmView : public QObject
{
    Q_OBJECT
public:
    explicit AlarmView(QObject *parent = nullptr);
    Q_INVOKABLE void stopAlarm();
    Q_INVOKABLE void snooze15min();
    Q_INVOKABLE void snooze10min();
    Q_INVOKABLE void snooze5min();

private:
    bool isSnooze = false;
    bool systemdSupportExist = false;
    void snooze(int min);
    const QString ALARM_TIMER = "alarm.timer";
    const QString ALARM_SERVICE = "alarm.service";

    const QString ALARM_SNOOZE_SERVICE = "alarm_snooze.service";
    const QString ALARM_SNOOZE_TIMER = "alarm_snooze.timer";

    QString CONFIG_PATH = "/etc/mediaserver";
    EditAlarmConfigFile editAlarmConfigFile;
};

#endif// ALARMVIEW_H
