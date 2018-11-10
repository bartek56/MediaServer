#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QProcess>
#include <memory>
#include "editwificonfigfile.h"

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

signals:

public slots:

private:
    EditWifiConfigFile editWifiConfigFile;
    std::vector<WifiConfigsName> vWifiConfigs;
    QObject* bConnect;
    QObject* bScanNetwork;
    bool wifiIsOn;
};

#endif // SETTINGS_H
