#include "managementofexternaldevices.h"
#include <QProcess>
#include <QDebug>
#include <QFile>

ManagementOfExternalDevices::ManagementOfExternalDevices()
{

}

QStringList ManagementOfExternalDevices::LoadExternalDevices()
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "lsblk -no LABEL");

    process.setReadChannel(QProcess::StandardOutput);
    QStringList devicesList;
    while(process.waitForFinished(-1));
    while (process.canReadLine())
    {
       auto line = process.readLine();
       if (line.size()>1)
       {
            line.remove(line.length()-1,1);
            QString qstrLine(line);
            devicesList.push_back(qstrLine);
       }
    }
    return devicesList;
}

std::map<QString, QString> ManagementOfExternalDevices::LoadDeviceParameters(const QString &deviceName)
{
    std::map<QString, QString> deviceParameters;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commend;
    commend << "-c" << "lsblk -rnio LABEL,SIZE,MOUNTPOINT,NAME | grep " + deviceName;
    process.start("bash", commend);
    process.setReadChannel(QProcess::StandardOutput);
    QStringList devicesList;
    while(process.waitForFinished());
    QByteArray line = process.readAll();

    auto par = line.split(' ');

    auto label = par[0];
    auto size = par[1];
    auto mountPoint = par[2];
    auto name = par[3];

    name=name.remove(name.length()-1,1);

    deviceParameters.insert(std::make_pair("LABEL",label));
    deviceParameters.insert(std::make_pair("SIZE",size));
    deviceParameters.insert(std::make_pair("MOUNTPOINT",mountPoint));
    deviceParameters.insert(std::make_pair("NAME",name));

    return deviceParameters;
}


void ManagementOfExternalDevices::MountDevice(const QString &deviceName, const QString &deviceLabel, const bool &automount)
{
    if(automount)
    {
        EnableAutomount(deviceName,deviceLabel);
    }

    QString mountpoint = "/mnt/" + deviceLabel;
    QString commend = "mkdir " + mountpoint;
    QProcess::execute(commend);

    commend = "mount /dev/" + deviceName + " " +mountpoint;
    QProcess::execute(commend);
}

void ManagementOfExternalDevices::UmountDevice(const QString &deviceName, const QString &mountpoint)
{
    DisableAutomount(deviceName);

    QString commend = "umount /dev/" + deviceName;
    QProcess::execute(commend);

    commend = "rm -r " +mountpoint;
    QProcess::execute(commend);
}

void ManagementOfExternalDevices::EnableAutomount(const QString &deviceName, const QString &deviceLabel)
{
    QStringList automountCommend;
    automountCommend << "-c" << "echo \"/dev/" + deviceName + "  /mnt/"+deviceLabel+" vfat   defaults    0   1 \" >> /etc/fstab";
    QProcess sh;
    sh.start("sh", automountCommend);
    sh.waitForFinished();
    sh.close();
}


void ManagementOfExternalDevices::DisableAutomount(const QString &deviceName)
{
    QFile file ("/etc/fstab");
    QStringList vUsers;
    bool deviceIsinAutomountList=false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString qstrLine(line);

        if(qstrLine.contains(deviceName))
        {
            deviceIsinAutomountList=true;
        }
        else
        {
            vUsers.push_back(line);
        }
    }
    file.close();

    if(deviceIsinAutomountList)
    {
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);
        for (auto it = std::begin(vUsers); it!=std::end(vUsers); ++it)
        {
            out << *it;
        }
    }
}
