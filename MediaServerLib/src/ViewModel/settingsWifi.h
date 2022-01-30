#ifndef SETTINGS_WIFI_H
#define SETTINGS_WIFI_H

#include "../editwificonfigfile.h"
#include "../editalarmconfigfile.h"

#include <QProcess>
#include <QtQuick>
#include <QObject>
#include <memory>

class SettingsWifi : public QObject
{

public:
    const QString WPASUPPLICANT_SERVICE = "wpa_supplicant.service";
    Q_OBJECT
public:
    explicit SettingsWifi(QObject *parent = nullptr);

    // Wifi
    Q_INVOKABLE void searchNetworks(QObject *obj);
    Q_INVOKABLE void updateWifiStatus(QObject *obj);
    Q_INVOKABLE void connect(const QString networkName, const QString password);
    Q_INVOKABLE void loadWifiConfigFile();
    Q_INVOKABLE void cbNetworks_onDisplayTextChanged(QString networkName, QObject *obj);
    Q_INVOKABLE void sWifiOn_OnCheckedChanged(bool wifiOnSwitch);
    Q_INVOKABLE void checkWifi(QObject *obj);

private:
    // Wifi Config
    QObject *bConnect;
    QObject *bScanNetwork;
    bool wifiIsOn;
    EditWifiConfigFile editWifiConfigFile;
    std::vector<WifiConfigsName> vWifiConfigs;
};

#endif// SETTINGS_H
