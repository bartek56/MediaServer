#include "alarmview.h"
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QtSystemd/unit.h>
#include <QtSystemd/sdmanager.h>
#include <QApplication>

AlarmView::AlarmView(QObject *parent) : QObject(parent)
{
    auto state = Systemd::getUnitFileState(Systemd::System, ALARM_SNOOZE_SERVICE);

    if(state.contains("able"))
    {
        Systemd::getUnit(Systemd::System, ALARM_SNOOZE_SERVICE);//support QDBusAbstractInterfaceSupport
        auto alarmSnoozeState = Systemd::loadUnit(Systemd::System, ALARM_SNOOZE_SERVICE)->activeState();
        auto alarmState = Systemd::loadUnit(Systemd::System, ALARM_SERVICE)->activeState();

        if(!alarmSnoozeState.contains("in"))
        {
            isSnooze = true;
        }
        if(!alarmSnoozeState.contains("in") || !alarmState.contains("in"))
        {
            systemdSupportExist = true;
        }
    }
    else
    {
        qDebug() << "alarm service not exist";
    }
}

void AlarmView::stopAlarm()
{
    if(systemdSupportExist)
    {
        Systemd::stopUnit(Systemd::System, ALARM_SNOOZE_TIMER, Systemd::Unit::Replace);

        if(isSnooze)
            Systemd::stopUnit(Systemd::System, ALARM_SNOOZE_SERVICE, Systemd::Unit::Replace);

        else
            Systemd::stopUnit(Systemd::System, ALARM_SERVICE, Systemd::Unit::Replace);

        auto alarmConfigMap = editAlarmConfigFile.LoadConfiguration();
        QString defaultVolume = alarmConfigMap["defaultVolume"];
        QProcess::startDetached("mpc", QStringList() << "volume " << defaultVolume);
    }
}

void AlarmView::snooze5min()
{
    if(systemdSupportExist)
        snooze(5);
}

void AlarmView::snooze10min()
{
    if(systemdSupportExist)
        snooze(10);
}

void AlarmView::snooze15min()
{
    if(systemdSupportExist)
        snooze(15);
}

void AlarmView::snooze(int min)
{
    QFile file(CONFIG_PATH + "/" + ALARM_SNOOZE_TIMER);

    QStringList vUsers;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString qstrLine(line);

        if(qstrLine.contains("OnCalendar"))
        {
            QDateTime local(QDateTime::currentDateTime());
            local = local.addSecs(60 * min);
            vUsers.push_back("OnCalendar=*-*-* " + local.toString("hh:mm") + "\n");
        }
        else
        {
            vUsers.push_back(line);
        }
    }

    file.close();

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for(auto it = std::begin(vUsers); it != std::end(vUsers); ++it)
    {
        out << *it;
    }
    file.close();

    QFile systemdVarFile("/etc/mediaserver/systemdVariables");

    QStringList arg;

    arg.push_back("ARG1=restart\n");

    if(!systemdVarFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream streamOut(&systemdVarFile);
    for(auto it = std::begin(arg); it != std::end(arg); ++it)
    {
        streamOut << *it;
    }
    systemdVarFile.close();

    Systemd::reload(Systemd::System);

    QProcess::startDetached("mpc", QStringList() << "stop");
    Systemd::restartUnit(Systemd::System, ALARM_SNOOZE_TIMER, Systemd::Unit::Replace);

    if(isSnooze)
        Systemd::stopUnit(Systemd::System, ALARM_SNOOZE_SERVICE, Systemd::Unit::Replace);
    else
        Systemd::stopUnit(Systemd::System, ALARM_SERVICE, Systemd::Unit::Replace);
}
