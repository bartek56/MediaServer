#ifndef MANAGEMENTOFEXTERNALDEVICES_H
#define MANAGEMENTOFEXTERNALDEVICES_H

#include <QString>
#include <map>
#include <vector>

class ManagementOfExternalDevices
{
public:
    ManagementOfExternalDevices();
    QStringList LoadExternalDevices();
    std::map<QString, QString> LoadDeviceParameters(const QString &deviceName);
    void MountDevice(const QString &deviceName, const QString &deviceLabel);
    void UmountDevice(const QString &deviceName, const QString &mountpoint);
};

#endif // MANAGEMENTOFEXTERNALDEVICES_H
