#ifndef MANAGEMENTOFEXTERNALDEVICES_H
#define MANAGEMENTOFEXTERNALDEVICES_H

#include <QString>
#include <map>
#include <vector>
#include <QProcess>
#include <QFile>

class ManagementOfExternalDevices
{
public:
    QStringList LoadExternalDevices();
    std::map<QString, QString> LoadDeviceParameters(const QString &deviceName);
};

#endif // MANAGEMENTOFEXTERNALDEVICES_H
