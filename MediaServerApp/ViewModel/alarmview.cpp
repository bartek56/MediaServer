
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

    QProcess::execute("systemctl stop alarm.service");
    QProcess::execute("mpc volume 60");
    QProcess::execute("systemctl restart start.service");

}
