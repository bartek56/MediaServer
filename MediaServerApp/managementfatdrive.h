#ifndef MANAGEMENTFATDRIVE_H
#define MANAGEMENTFATDRIVE_H
#include "managementofexternaldevices.h"

class ManagementFatDrive : public ManagementOfExternalDevices
{
public:
    //ManagementFatDrive():ManagementOfExternalDevices(){}
    virtual void MountDevice(const QString &deviceName, const QString &deviceLabel, const QString &type, const bool &automount) override;
    virtual void UmountDevice(const QString &deviceName, const QString &mountpoint) override;
    virtual void EnableAutomount(const QString &deviceName, const QString &deviceLabel) override;
    virtual void DisableAutomount(const QString &deviceName) override;
};

#endif // MANAGEMENTFATDRIVE_H
