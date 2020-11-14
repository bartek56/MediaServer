#include "managementofexternaldevices.h"


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
    process.close();

    return devicesList;
}

std::map<QString, QString> ManagementOfExternalDevices::LoadDeviceParameters(const QString &label)
{
    std::map<QString, QString> deviceParameters;

    QProcess processReadLabel;
    processReadLabel.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commend;
    commend << "-c" << "lsblk -lno LABEL,NAME | grep '" + label + "'";
    processReadLabel.start("bash", commend);

    processReadLabel.setReadChannel(QProcess::StandardOutput);
    while(processReadLabel.waitForFinished());


    QByteArray labelLine = processReadLabel.readAll();
    processReadLabel.close();
    QString name;
    for(auto it=labelLine.end()-2; it!=labelLine.begin();--it)
    {
        if(*it==' ')
        {
            break;
        }
        name.push_front(*it);
    }

    QProcess processReadParameters;
    processReadParameters.setProcessChannelMode(QProcess::MergedChannels);
    QStringList commend2;
    //commend << "-c" << "lsblk -rnio LABEL,SIZE,MOUNTPOINT,NAME | grep " + deviceName;
    commend2 << "-c" << "lsblk -rnio NAME,SIZE,FSTYPE,MOUNTPOINT | grep '" + name + "'";
    processReadParameters.start("bash", commend2);
    processReadParameters.setReadChannel(QProcess::StandardOutput);
    while(processReadParameters.waitForFinished());
    QByteArray parametersLine = processReadParameters.readAll();
    processReadParameters.close();

    auto par = parametersLine.split(' ');

    auto size = par[1];
    auto type = par[2];
    auto mountPoint = par[3];

    deviceParameters.insert(std::make_pair("LABEL",label));
    deviceParameters.insert(std::make_pair("SIZE",size));
    if(mountPoint.size()>2)
        deviceParameters.insert(std::make_pair("MOUNTPOINT","/mnt/"+label));
    else
        deviceParameters.insert(std::make_pair("MOUNTPOINT"," "));

    deviceParameters.insert(std::make_pair("NAME",name));
    deviceParameters.insert(std::make_pair("TYPE",type));

    return deviceParameters;
}
