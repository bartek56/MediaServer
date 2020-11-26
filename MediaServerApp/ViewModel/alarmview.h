#ifndef ALARMVIEW_H
#define ALARMVIEW_H

#include <QObject>
#include "editalarmconfigfile.h"
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
    bool isSnooze;
    void snooze(int min);
    const QString ALARM_TIMER = "alarm.timer";
    QString CONFIG_PATH = "/etc/mediaserver";
    EditAlarmConfigFile editAlarmConfigFile;

};

#endif // ALARMVIEW_H
