#include "massstorage.h"
#include <QDebug>

MassStorage::MassStorage(QObject *parent) : QObject(parent)
{

}
void MassStorage::loadExternalDevices(QObject *devicesList, QObject *mountButton)
{
    managementExternalDevices = new ManagementOfExternalDevices;
    auto deviceList = managementExternalDevices->LoadExternalDevices();
    devicesList->setProperty("model",QVariant(deviceList));
    if(deviceList.count()>0)
    {
        mountButton->setProperty("enabled",QVariant(true));
    }
}

void MassStorage::cbDevices_onDisplayTextChanged(QString deviceName, QObject *deviceSizeText, QObject *nameDeviceText,QObject *mountPointText, QObject *typeText)
{
    auto deviceParametersMap = managementExternalDevices->LoadDeviceParameters(deviceName);
    deviceSizeText->setProperty("text",QVariant(deviceParametersMap.at("SIZE")));
    nameDeviceText->setProperty("text",QVariant(deviceParametersMap.at("NAME")));
    mountPointText->setProperty("text",QVariant(deviceParametersMap.at("MOUNTPOINT")));
    typeText -> setProperty("text",QVariant(deviceParametersMap.at("TYPE")));
}

void MassStorage::bMount_onClicked(const QString mountpoint,const QString deviceName, QString deviceLabel, const bool autoMount, const QString type)
{
    //fstab_manager.sh true sda7 "/mnt/TOSHIBA EXT2" ntfs-3g
    if(mountpoint.count()>2) // umount
    {
        QProcess::execute("bash /opt/fstab_manager.sh false " + deviceName);

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
    else // mount
    {
        QString mountpoint = "/mnt/'" + deviceLabel + "'";
        QString commend = "mkdir -p " + mountpoint;

        QProcess process;
        process.setProcessChannelMode(QProcess::MergedChannels);
        QStringList commend_new;
        commend_new << "-c" << commend;
        process.start("bash", commend_new);
        while(process.waitForFinished());
        process.close();

        if(type=="ntfs")
        {
            commend = "ntfs-3g /dev/" + deviceName + " " + mountpoint;
        }
        else
        {
            commend = "mount /dev/" + deviceName + " " + mountpoint;
        }

        QProcess process2;
        process2.setProcessChannelMode(QProcess::MergedChannels);
        QStringList commend_new2;
        commend_new2 << "-c" << commend;
        process2.start("bash", commend_new2);
        while(process2.waitForFinished());
        process2.close();

        if(autoMount)
        {
            QString mountPath = "/mnt/"+deviceLabel;
            QProcess::execute("bash /opt/fstab_manager.sh true \"" + deviceName + "\" \"" + mountPath + "\" " + type);
        }
    }
}
