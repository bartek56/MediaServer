
#include "alarmview.h"
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <QDateTime>

AlarmView::AlarmView(QObject *parent) : QObject(parent)
{
    isSnooze = false;
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active alarm_snooze.service");
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    if(!text.contains("in")) // alarm active
    {
        isSnooze = true;
    }
}

void AlarmView::stopAlarm()
{
    auto alarmConfigMap = editAlarmConfigFile.LoadConfiguration();

    QString defaultVolume = alarmConfigMap["defaultVolume"];
    QProcess::startDetached("systemctl stop alarm_snooze.timer");
    if(isSnooze)
        QProcess::startDetached("systemctl stop alarm_snooze.service");
    else
        QProcess::startDetached("systemctl stop alarm.service");

    QProcess::startDetached("mpc volume "+defaultVolume);
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
    QFile file (CONFIG_PATH+"/alarm_snooze.timer");

    QStringList vUsers;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString qstrLine(line);

        if(qstrLine.contains("OnCalendar"))
        {
            QDateTime local(QDateTime::currentDateTime());
            local = local.addSecs(60*min);
            vUsers.push_back("OnCalendar=*-*-* "+local.toString("hh:mm")+"\n");
        }
        else
        {
            vUsers.push_back(line);
        }
    }

    file.close();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (auto it = std::begin(vUsers); it!=std::end(vUsers); ++it)
    {
        out << *it;
    }
    file.close();

    QFile systemdVarFile ("/etc/mediaserver/systemdVariables");

    QStringList arg;

    arg.push_back("ARG1=restart\n");

    if (!systemdVarFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream streamOut(&systemdVarFile);
    for (auto it = std::begin(arg); it!=std::end(arg); ++it)
    {
        streamOut << *it;
    }
    systemdVarFile.close();

    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("systemctl daemon-reload");

    while(builder.waitForFinished());
    QProcess::startDetached("mpc stop");
    QProcess::startDetached("systemctl restart alarm_snooze.timer");

    if(isSnooze)
        QProcess::startDetached("systemctl stop alarm_snooze.service");
    else
        QProcess::startDetached("systemctl stop alarm.service");
    QProcess::startDetached("systemctl stop alarm_gui.service");


}
