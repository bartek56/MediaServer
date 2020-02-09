#include "settings.h"

void Settings::loadExternalDevices(QObject *devicesList, QObject *mountButton)
{
    managementExternalDevices = new ManagementOfExternalDevices;
    auto deviceList = managementExternalDevices->LoadExternalDevices();
    devicesList->setProperty("model",QVariant(deviceList));
    if(deviceList.count()>0)
    {
        mountButton->setProperty("enabled",QVariant(true));
    }
}

void Settings::cbDevices_onDisplayTextChanged(QString deviceName, QObject *deviceSizeText, QObject *nameDeviceText,QObject *mountPointText, QObject *typeText)
{
    auto deviceParametersMap = managementExternalDevices->LoadDeviceParameters(deviceName);
    deviceSizeText->setProperty("text",QVariant(deviceParametersMap.at("SIZE")));
    nameDeviceText->setProperty("text",QVariant(deviceParametersMap.at("NAME")));
    mountPointText->setProperty("text",QVariant(deviceParametersMap.at("MOUNTPOINT")));  
    typeText -> setProperty("text",QVariant(deviceParametersMap.at("TYPE")));

    if(deviceParametersMap.at("TYPE")=="ntfs")
    {
        managementExternalDevices = new ManagementNtfsDrive;
    }
    else
    {
        managementExternalDevices = new ManagementFatDrive;
    }

}

void Settings::bMount_onClicked(const QString mountpoint,const QString deviceName, QString deviceLabel, const bool autoMount, const QString type)
{
    if(mountpoint.count()>2)
    {
        managementExternalDevices->UmountDevice(deviceName, mountpoint);
    }
    else
    {
        managementExternalDevices->MountDevice(deviceName, deviceLabel, type, autoMount);
    }
}
