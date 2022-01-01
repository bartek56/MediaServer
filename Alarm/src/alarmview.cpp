#include "alarmview.h"
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QtSystemd/unit.h>
#include <QtSystemd/sdmanager.h>

AlarmView::AlarmView(QObject *parent) : QObject(parent)
{
    const QString unitName("alarm_snooze.service");
    auto text = Systemd::getUnit(Systemd::System, unitName).data()->activeState();

    if(!text.contains("in"))// alarm active
    {
        isSnooze = true;
    }
}

void AlarmView::stopAlarm()
{
    Systemd::stopUnit(Systemd::System, "alarm_snooze.timer", Systemd::Unit::Replace);

    if(isSnooze)
        Systemd::stopUnit(Systemd::System, "alarm_snooze.service", Systemd::Unit::Replace);

    else
        Systemd::stopUnit(Systemd::System, "alarm.service", Systemd::Unit::Replace);

    auto alarmConfigMap = editAlarmConfigFile.LoadConfiguration();
    QString defaultVolume = alarmConfigMap["defaultVolume"];
    QProcess::startDetached("mpc", QStringList() << "volume " << defaultVolume);
}

void AlarmView::snooze5min()
{
    snooze(5);
}

void AlarmView::snooze10min()
{
    snooze(10);
}

void AlarmView::snooze15min()
{
    snooze(15);
}

void AlarmView::snooze(int min)
{
    QFile file(CONFIG_PATH + "/alarm_snooze.timer");

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
    Systemd::restartUnit(Systemd::System, "alarm_snooze.timer", Systemd::Unit::Replace);

    if(isSnooze)
        Systemd::stopUnit(Systemd::System, "alarm_snooze.service", Systemd::Unit::Replace);
    else
        Systemd::stopUnit(Systemd::System, "alarm.service", Systemd::Unit::Replace);

    QProcess::startDetached("systemctl", QStringList() << "stop"
                                                       << "alarm_gui.service");
}
