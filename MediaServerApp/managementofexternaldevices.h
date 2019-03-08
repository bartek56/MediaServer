#ifndef MANAGEMENTOFEXTERNALDEVICES_H
#define MANAGEMENTOFEXTERNALDEVICES_H

#include <QString>
#include <map>
#include <vector>
#include <QProcess>
#include <QDebug>
#include <QFile>

class ManagementOfExternalDevices
{
public:
    QStringList LoadExternalDevices();
    std::map<QString, QString> LoadDeviceParameters(const QString &deviceName);
    virtual void MountDevice(const QString &deviceName, const QString &deviceLabel, const QString &type, const bool &automount);
    virtual void UmountDevice(const QString &deviceName, const QString &mountpoint);
    virtual void EnableAutomount(const QString &deviceName, const QString &deviceLabel);
    virtual void DisableAutomount(const QString &deviceName);
    virtual ~ManagementOfExternalDevices(){}
};

#endif // MANAGEMENTOFEXTERNALDEVICES_H
