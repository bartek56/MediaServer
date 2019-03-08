#ifndef MANAGEMENTNTFSDRIVE_H
#define MANAGEMENTNTFSDRIVE_H
#include "managementofexternaldevices.h"

class ManagementNtfsDrive : public ManagementOfExternalDevices
{
public:
    //ManagementNtfsDrive():ManagementOfExternalDevices(){}
    virtual void MountDevice(const QString &deviceName, const QString &deviceLabel, const QString &type, const bool &automount) override;
    virtual void UmountDevice(const QString &deviceName, const QString &mountpoint) override;
    virtual void EnableAutomount(const QString &deviceName, const QString &deviceLabel) override;
    virtual void DisableAutomount(const QString &deviceName) override;
};

#endif // MANAGEMENTNTFSDRIVE_H
