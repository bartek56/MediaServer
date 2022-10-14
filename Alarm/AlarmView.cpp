#include "AlarmView.h"
#include "ConfigFile/ConfigFile.h"
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QtSystemd/unit.h>
#include <QtSystemd/sdmanager.h>

AlarmView::AlarmView(QObject *parent) : QObject(parent)
  ,editAlarmConfigFile(std::make_shared<ConfigFile>(ALARM_CONFIG_FILE))
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
        qWarning() << "alarm service not exist";
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

        VectorData alarmConfigMap;
        editAlarmConfigFile.LoadConfiguration(alarmConfigMap);
        QString defaultVolume = alarmConfigMap.getValueByKey("defaultVolume");
        QProcess::startDetached("mpc", QStringList() << "volume" << defaultVolume);
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
    QFile file(QString(CONFIG_PATH) + "/" + ALARM_SNOOZE_TIMER);

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

    Systemd::reload(Systemd::System);

    QProcess::startDetached("mpc", QStringList() << "stop");
    Systemd::restartUnit(Systemd::System, ALARM_SNOOZE_TIMER, Systemd::Unit::Replace);

    if(isSnooze)
        Systemd::stopUnit(Systemd::System, ALARM_SNOOZE_SERVICE, Systemd::Unit::Replace);
    else
        Systemd::stopUnit(Systemd::System, ALARM_SERVICE, Systemd::Unit::Replace);
}
