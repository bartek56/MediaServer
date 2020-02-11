
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
    QStringList devicesList;
    process.waitForFinished();
    auto text = process.readAll();
    if(!text.contains("in")) // alarm active
    {
        isSnooze = true;
    }

}


void AlarmView::stopAlarm()
{
    qDebug() << "stopAlarm";
    QProcess::startDetached("mpc volume 20");
    QProcess::startDetached("systemctl stop alarm_snooze.timer");
    QProcess::startDetached("systemctl start gmpc");

    QFile systemdVarFile ("/etc/systemdVariables");

    QStringList arg;

    arg.push_back("ARG1=stop\n");

     if (!systemdVarFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

     QTextStream streamOut(&systemdVarFile);
     for (auto it = std::begin(arg); it!=std::end(arg); ++it)
     {
         streamOut << *it;
     }
    systemdVarFile.close();

    if(isSnooze)
        QProcess::startDetached("systemctl stop alarm_snooze.service");
    else
        QProcess::startDetached("systemctl stop alarm.service");

}

void AlarmView::snooze()
{
    qDebug() << "snooze";

    QFile file ("/usr/lib/systemd/system/alarm_snooze.timer");

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
            local = local.addSecs(60*9);
            vUsers.push_back("OnCalendar=*-*-* "+local.toString("hh:mm:ss")+"\n");
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


     QFile systemdVarFile ("/etc/systemdVariables");

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

    QProcess::startDetached("mpc stop");
    QProcess::startDetached("systemctl restart alarm_snooze.timer");

    if(isSnooze)
        QProcess::startDetached("systemctl stop alarm_snooze.service");
    else
        QProcess::startDetached("systemctl stop alarm.service");

}
