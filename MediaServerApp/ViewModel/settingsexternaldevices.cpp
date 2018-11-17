#include "settings.h"

void Settings::loadExternalDevices(QObject *obj)
{
    auto deviceList = managementExternalDevices.LoadExternalDevices();
    obj->setProperty("model",QVariant(deviceList));
}

void Settings::cbDevices_onDisplayTextChanged(QString deviceName, QObject *deviceSizeText, QObject *nameDeviceText,QObject *mountPointText)
{
    auto deviceParametersMap = managementExternalDevices.LoadDeviceParameters(deviceName);
    deviceSizeText->setProperty("text",QVariant(deviceParametersMap.at("SIZE")));
    nameDeviceText->setProperty("text",QVariant(deviceParametersMap.at("NAME")));
    mountPointText->setProperty("text",QVariant(deviceParametersMap.at("MOUNTPOINT")));
}

void Settings::bMount_onClicked(const QString mountpoint,const QString deviceName, const QString deviceLabel)
{
    if(mountpoint.count()>1)
    {
        managementExternalDevices.UmountDevice(deviceName,mountpoint);
    }
    else
    {
        managementExternalDevices.MountDevice(deviceName, deviceLabel);
    }
}
