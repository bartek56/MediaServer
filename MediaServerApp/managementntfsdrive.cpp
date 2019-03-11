#include "managementntfsdrive.h"

void ManagementNtfsDrive::MountDevice(const QString &deviceName, const QString &deviceLabel, const QString &type, const bool &automount)
{
    if(automount)
    {
        EnableAutomount(deviceName,deviceLabel);
    }

    QString mountpoint = "/mnt/'" + deviceLabel  + "'";
    QString commendMakeDir = "mkdir -p " + mountpoint;

    QProcess processMakeDir;
    processMakeDir.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commendMakeDirBash;
    commendMakeDirBash << "-c" << commendMakeDir;
    processMakeDir.start("bash", commendMakeDirBash);
    while(processMakeDir.waitForFinished());
    processMakeDir.close();

    QProcess processMount;
    processMount.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commendNtfsMountBash;
    QString commendNtfsMount = "ntfs-3g /dev/" + deviceName + " " +mountpoint;
    commendNtfsMountBash << "-c" << commendNtfsMount;
    processMount.start("bash", commendNtfsMountBash);
    while(processMount.waitForFinished());
    processMount.close();
}

void ManagementNtfsDrive::UmountDevice(const QString &deviceName, const QString &mountpoint)
{
    DisableAutomount(deviceName);

    QString commendUmount = "umount /dev/" + deviceName;

    QProcess processUmount;
    processUmount.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commendUmountBash;
    commendUmountBash << "-c" << commendUmount;
    processUmount.start("bash", commendUmountBash);
    while(processUmount.waitForFinished());
    processUmount.close();


    QString commendRemove = "rmdir '" +mountpoint+"'";
    QProcess processRemove;
    processRemove.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commendRemoveBash;
    commendRemoveBash << "-c" << commendRemove;
    processRemove.start("bash", commendRemoveBash);
    while(processRemove.waitForFinished());
    processRemove.close();

}

void ManagementNtfsDrive::EnableAutomount(const QString &deviceName, const QString &deviceLabel)
{
    QStringList automountCommend;
    automountCommend << "-c" << "echo \"/dev/" + deviceName + "  /mnt/'"+deviceLabel+"' ntfs   rw,auto,user    0   0 \" >> /etc/fstab";
    QProcess sh;
    sh.start("sh", automountCommend);
    while(sh.waitForFinished());
    sh.close();
}

void ManagementNtfsDrive::DisableAutomount(const QString &deviceName)
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
