#ifndef MASSSTORAGE_H
#define MASSSTORAGE_H

#include <QObject>
#include "ManagementOfExternalDevices.h"

class MassStorage : public QObject
{
    Q_OBJECT
public:
    explicit MassStorage(QObject *parent = nullptr);
    Q_INVOKABLE void loadExternalDevices(QObject *devicesList, QObject *mountButton);
    Q_INVOKABLE void cbDevices_onDisplayTextChanged(QString deviceName, QObject *deviceSizeText, QObject *nameDeviceText, QObject *mountPointText, QObject *typeText);
    Q_INVOKABLE void bMount_onClicked(const QString mountpoint,const QString deviceName, QString deviceLabel, const bool automount, const QString type);

private:
    ManagementOfExternalDevices *managementExternalDevices;
};

#endif // MASSSTORAGE_H
