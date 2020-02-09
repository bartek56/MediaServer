#include "managementfatdrive.h"


void ManagementFatDrive::MountDevice(const QString &deviceName, QString &deviceLabel, const QString &type, const bool &automount)
{
    if(automount)
    {
        EnableAutomount(deviceName,deviceLabel);
    }
/*
    QString mountpoint = "/mnt/'" + deviceLabel  + "'";
    QString commend = "mkdir -p " + mountpoint;

    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commend_new;
    commend_new << "-c" << commend;
    process.start("bash", commend_new);
    while(process.waitForFinished());
    process.close();

    commend = "mount /dev/" + deviceName + " " +mountpoint;

    QProcess process2;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commend_new2;
    commend_new2 << "-c" << commend;
    process2.start("bash", commend_new2);
    while(process2.waitForFinished());
    process2.close();
    */
}

void ManagementFatDrive::UmountDevice(const QString &deviceName, const QString &mountpoint)
{
    DisableAutomount(deviceName);

    QString commend = "umount /dev/" + deviceName;
    QProcess::execute(commend);

    commend = "rmdir " +mountpoint;
    QProcess::execute(commend);
}

void ManagementFatDrive::EnableAutomount(const QString &deviceName, QString &deviceLabel)
{
    QStringList automountCommend;
    deviceLabel.replace(' ','\040');
    automountCommend << "-c" << "echo \"/dev/" + deviceName + "  /mnt/'"+deviceLabel+"' vfat   defaults    0   1 \" >> /etc/fstab";
    QProcess sh;
    sh.start("sh", automountCommend);
    sh.waitForFinished();
    sh.close();
}

void ManagementFatDrive::DisableAutomount(const QString &deviceName)
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
