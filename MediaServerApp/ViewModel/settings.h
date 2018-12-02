#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QProcess>
#include <memory>
#include <QtQuick>
#include "editwificonfigfile.h"
#include "editscreensaverconfigfile.h"
#include "managementofexternaldevices.h"


class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    Q_INVOKABLE void searchNetworks(QObject* obj);
    Q_INVOKABLE void updateWifiStatus(QObject* obj);
    Q_INVOKABLE void updateNetworkStatus(QObject* obj);
    Q_INVOKABLE void connect(const QString networkName, const QString password);
    Q_INVOKABLE void loadWifiConfigFile();
    Q_INVOKABLE void cbNetworks_onDisplayTextChanged(QString networkName, QObject *obj);
    Q_INVOKABLE void sWifiOn_OnCheckedChanged(bool wifiOnSwitch);
    Q_INVOKABLE void checkWifi(QObject *obj);
    Q_INVOKABLE void loadExternalDevices(QObject *obj);
    Q_INVOKABLE void cbDevices_onDisplayTextChanged(QString deviceName, QObject *deviceSizeText, QObject *nameDeviceText,QObject *mountPointText);
    Q_INVOKABLE void bMount_onClicked(const QString mountpoint,const QString deviceName, const QString deviceLabel, const bool automount);
    Q_INVOKABLE void bSaveScreenSaver_onClicked(const QString timeout, const QString path, const int startTime,const bool random);
    Q_INVOKABLE void bScreenSaverFileDialog_onAccepted(QString folderPath, QObject *tfScreenSavrFolderPath);
    Q_INVOKABLE void loadScreenSaverConfigurations(QObject *startTime, QObject *path, QObject *timeout,QObject *random);

signals:

public slots:

private:
    EditWifiConfigFile editWifiConfigFile;
    EditScreenSaverConfigFile editScreenSaverConfigFile;
    ManagementOfExternalDevices managementExternalDevices;
    std::vector<WifiConfigsName> vWifiConfigs;
    std::map<QString, QString> mScreenSaverConfigs;
    int ConvertTimeFromMiliSecStringToMinutesInt(QString milisec);
    QObject* bConnect;
    QObject* bScanNetwork;
    bool wifiIsOn;
};

#endif // SETTINGS_H
