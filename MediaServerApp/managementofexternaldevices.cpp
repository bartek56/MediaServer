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
    while(process.waitForFinished());
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

std::map<QString, QString> ManagementOfExternalDevices::LoadDeviceParameters(const QString &label)
{
    std::map<QString, QString> deviceParameters;

            QProcess process;
            process.setProcessChannelMode(QProcess::MergedChannels);
            QStringList commend;
            //commend << "-c" << "lsblk -rnio LABEL,SIZE,MOUNTPOINT,NAME | grep " + deviceName;
            commend << "-c" << "lsblk -lno LABEL,NAME | grep '" + label + "'";
            process.start("bash", commend);
            qDebug() << commend;
            process.setReadChannel(QProcess::StandardOutput);
            while(process.waitForFinished());
            QByteArray line = process.readAll();
            qDebug() << line;
            QString name;
            for(auto it=line.end()-2; it!=line.begin();--it)
            {
                if(*it==' ')
                {
                    break;
                }
                name.push_front(*it);
            }

            qDebug() << name;


    QProcess process2;
    process2.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commend2;
    //commend << "-c" << "lsblk -rnio LABEL,SIZE,MOUNTPOINT,NAME | grep " + deviceName;
    commend2 << "-c" << "lsblk -rnio NAME,SIZE,FSTYPE,MOUNTPOINT | grep '" + name + "'";
    process2.start("bash", commend2);
    process2.setReadChannel(QProcess::StandardOutput);
    QStringList devicesList;
    while(process2.waitForFinished());
    QByteArray line2 = process2.readAll();
    qDebug() << line2;
    auto par = line2.split(' ');

    auto size = par[1];
    auto type = par[2];
    auto mountPoint = par[3];

    deviceParameters.insert(std::make_pair("LABEL",label));
    deviceParameters.insert(std::make_pair("SIZE",size));
    deviceParameters.insert(std::make_pair("MOUNTPOINT",mountPoint));
    deviceParameters.insert(std::make_pair("NAME",name));
    deviceParameters.insert(std::make_pair("TYPE",type));

    return deviceParameters;
}


void ManagementOfExternalDevices::MountDevice(const QString &deviceName, const QString &deviceLabel, const QString &type, const bool &automount)
{
    /*
    if(automount)
    {
        EnableAutomount(deviceName,deviceLabel);
    }
    */




    QString mountpoint = "/mnt/'" + deviceLabel  + "'";
    QString commend = "mkdir " + mountpoint;
    qDebug() << commend;
    //QProcess::execute(commend);
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    //commend << "-c" << "lsblk -rnio LABEL,SIZE,MOUNTPOINT,NAME | grep " + deviceName;
    QStringList commend_new;
    commend_new << "-c" << commend;
    process.start("bash", commend_new);
    while(process.waitForFinished());
    if(type=="ntfs")
    {
        commend = "ntfs-3g /dev/" + deviceName + " " +mountpoint;
    }
    else
    {
        commend = "mount /dev/" + deviceName + " " +mountpoint;
    }

    qDebug() << commend;

    //QProcess process2;
    //process2.setProcessChannelMode(QProcess::MergedChannels);
    //QStringList commend2;
    //commend << "-c" << "lsblk -rnio LABEL,SIZE,MOUNTPOINT,NAME | grep " + deviceName;
    //commend2 << "-c" << "lsblk -rnio NAME,SIZE,FSTYPE,MOUNTPOINT | grep '" + name + "'";
    //process2.start("bash", commend2);
    QProcess process2;
    process.setProcessChannelMode(QProcess::MergedChannels);
    //commend << "-c" << "lsblk -rnio LABEL,SIZE,MOUNTPOINT,NAME | grep " + deviceName;
    QStringList commend_new2;
    commend_new2 << "-c" << commend;
    process2.start("bash", commend_new2);
    while(process2.waitForFinished());
    //QProcess::execute(commend);
}

void ManagementOfExternalDevices::UmountDevice(const QString &deviceName, const QString &mountpoint)
{
    //DisableAutomount(deviceName);

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
