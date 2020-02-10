
#include "alarmview.h"
#include <QProcess>
#include <QDebug>
AlarmView::AlarmView(QObject *parent) : QObject(parent)
{

}

void AlarmView::stopAlarm()
{
    qDebug() << "stopAlarm";
}

void AlarmView::snooze()
{
    qDebug() << "snooze";

    QProcess::startDetached("mpc volume 60");
    QProcess::startDetached("systemctl stop alarm.service");
}
