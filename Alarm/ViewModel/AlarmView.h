#ifndef ALARMVIEW_H
#define ALARMVIEW_H

#include <QObject>
#include "ConfigFile/AlarmConfigFile.h"

class AlarmView : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString currentSong READ currentSong NOTIFY currentSongChanged)
    Q_PROPERTY(QString alarmTime READ alarmTime CONSTANT)
public:
    explicit AlarmView(QObject *parent = nullptr);
    QString currentSong() const { return m_currentSong; }
    QString alarmTime() const { return m_alarmTime; }
    Q_INVOKABLE void refreshCurrentSong();
    Q_INVOKABLE void stopAlarm();
    Q_INVOKABLE void snooze15min();
    Q_INVOKABLE void snooze10min();
    Q_INVOKABLE void snooze5min();

private:
    QString m_currentSong;
    QString m_alarmTime = QStringLiteral("07:30");
    void setCurrentSong(const QString &song);
    void loadAlarmTime();
signals:
    void currentSongChanged();

private:
    bool isSnooze = false;
    bool systemdSupportExist = false;
    void snooze(int min);
    const QString ALARM_TIMER = "alarm.timer";
    const QString ALARM_SERVICE = "alarm.service";

    const QString ALARM_SNOOZE_SERVICE = "alarm_snooze.service";
    const QString ALARM_SNOOZE_TIMER = "alarm_snooze.timer";

    AlarmConfigFile editAlarmConfigFile;
};

#endif// ALARMVIEW_H
