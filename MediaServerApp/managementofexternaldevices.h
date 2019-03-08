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
    void MountDevice(const QString &deviceName, const QString &deviceLabel, const QString &type, const bool &automount);
    void UmountDevice(const QString &deviceName, const QString &mountpoint);

private:
    void EnableAutomount(const QString &deviceName, const QString &deviceLabel);
    void DisableAutomount(const QString &deviceName);
};

#endif // MANAGEMENTOFEXTERNALDEVICES_H
