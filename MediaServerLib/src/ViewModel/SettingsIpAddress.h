#ifndef SETTINGS_IP_ADDRESS_H
#define SETTINGS_IP_ADDRESS_H

#include "../EditWifiConfigFile.h"
#include "../EditAlarmConfigFile.h"

#include <QObject>
#include <memory>

struct NetworkConfig
{
    QString ipAddressWithMask;
    QString gateway;
    QString dns;
    bool DHCPisEnable;
};


class SettingsIpAddress : public QObject
{

public:
    Q_OBJECT
public:
    explicit SettingsIpAddress(QObject *parent = nullptr);
    ~SettingsIpAddress();

    // IP Address
    Q_INVOKABLE void loadIpAddressConfiguration(const int networkInterfaceIndexComboBox, QObject *dynamicIPRadioButton, QObject *staticIPRadioButton, QObject *ipadressTextField,
                                                QObject *netmaskTextField, QObject *gatewayTextField, QObject *dnsserverTextField);
    Q_INVOKABLE void tfIpAddress_onEditingFinished(const QString text);
    Q_INVOKABLE void tfNetMask_onEditingFinished(const QString text);
    Q_INVOKABLE void tfGateway_onEditingFinished(const QString text);
    Q_INVOKABLE void tfDNSServer_onEditingFinished(const QString text);
    Q_INVOKABLE void rbDynamicIP_onClicked();
    Q_INVOKABLE void rbStaticIP_onClicked(const QString ipadressTextField, const QString netmaskTextField, const QString gatewayTextField, const QString dnsserverTextField);
    Q_INVOKABLE void saveIpAddressConfiguration();

private:
    // IP Adress
    const QString ETHERNET_CONFIG_FILE = "/etc/mediaserver/10-wired.network";
    const QString WIFI_CONFIG_FILE = "/etc/mediaserver/20-wireless.network";
    std::shared_ptr<NetworkConfig> wifiSettings;
    std::shared_ptr<NetworkConfig> ethSettings;
    std::shared_ptr<NetworkConfig> ipSettings;
    QStringList splitString(const QString &str, int n);
    QString binToDec(QString bin);
    QString decToBin(QString dev);
    QString convertNetMaskToFull(QString decMask);
    QString convertNetMaskToShort(QString decMask);
    NetworkConfig loadNetworkConfig(const QString &configFile);
    void setCurrentIpAddressConfig(const int &networkInterfaceComboboxIndex);
};

#endif// SETTINGS_H
