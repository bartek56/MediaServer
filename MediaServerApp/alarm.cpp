#include "alarm.h"
#include <QProcess>

Alarm::Alarm()
{

}

void Alarm::AlarmCheckingActive()
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active alarm.service");
    process.setReadChannel(QProcess::StandardOutput);
    QStringList devicesList;
    process.waitForFinished();
    auto text = process.readAll();
    if(!text.contains("in")) // alarm active
    {

    }
}
