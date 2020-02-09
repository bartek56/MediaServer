#ifndef ALARMVIEW_H
#define ALARMVIEW_H

#include <QObject>

class AlarmView : public QObject
{
    Q_OBJECT
public:
    explicit AlarmView(QObject *parent = nullptr);
    Q_INVOKABLE void stopAlarm();
    Q_INVOKABLE void snooze();

signals:

public slots:
};

#endif // ALARMVIEW_H
