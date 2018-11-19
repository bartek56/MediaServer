#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QProcess>
#include <memory>
#include <QtQuick>
#include "editwificonfigfile.h"
#include "managementofexternaldevices.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    Q_INVOKABLE void searchNetworks(QObject* obj);
    Q_INVOKABLE void updateStatus(QObject* obj);
    Q_INVOKABLE void connect(const QString networkName, const QString password);
    Q_INVOKABLE void loadWifiConfigFile();
    Q_INVOKABLE void cbNetworks_onDisplayTextChanged(QString networkName, QObject *obj);
    Q_INVOKABLE void sWifiOn_OnCheckedChanged(bool wifiOnSwitch);
    Q_INVOKABLE void checkWifi(QObject *obj);
    Q_INVOKABLE void loadExternalDevices(QObject *obj);
    Q_INVOKABLE void cbDevices_onDisplayTextChanged(QString deviceName, QObject *deviceSizeText, QObject *nameDeviceText,QObject *mountPointText);
    Q_INVOKABLE void bMount_onClicked(const QString mountpoint,const QString deviceName, const QString deviceLabel, const bool automount);

signals:

public slots:

private:
    EditWifiConfigFile editWifiConfigFile;
    ManagementOfExternalDevices managementExternalDevices;
    std::vector<WifiConfigsName> vWifiConfigs;
    //std::vector<ExternalDevicesConfigs> vExternalDevices;
    QObject* bConnect;
    QObject* bScanNetwork;
    bool wifiIsOn;
};

#endif // SETTINGS_H