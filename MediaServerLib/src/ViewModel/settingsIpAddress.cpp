#include "settingsIpAddress.h"

#include <QtSystemd/sdmanager.h>
#include <QtSystemd/unit.h>
#include <QSettings>
#include <bitset>
#include <map>

SettingsIpAddress::SettingsIpAddress(QObject *parent) : QObject(parent)
{
    ethSettings = std::make_shared<NetworkConfig>(loadNetworkConfig(ETHERNET_CONFIG_FILE));
    wifiSettings = std::make_shared<NetworkConfig>(loadNetworkConfig(WIFI_CONFIG_FILE));
}

SettingsIpAddress::~SettingsIpAddress()
{
}

NetworkConfig SettingsIpAddress::loadNetworkConfig(const QString &configFile)
{
    QSettings settings(configFile, QSettings::IniFormat);
    NetworkConfig networkConfig;
    if(settings.allKeys().contains("Network/DHCP"))
    {
        if(settings.value("Network/DHCP").toString().contains("yes"))
            networkConfig.DHCPisEnable = true;
        else
            networkConfig.DHCPisEnable = false;
    }
    else
    {
        networkConfig.DHCPisEnable = false;
        networkConfig.dns = settings.value("Network/DNS").toString();
        networkConfig.gateway = settings.value("Network/Gateway").toString();
        networkConfig.ipAddressWithMask = settings.value("Network/Address").toString();
    }
    return networkConfig;
}


void SettingsIpAddress::loadIpAddressConfiguration(const int networkInterfaceComboboxIndex, QObject *dynamicIPRadioButton, QObject *staticIPRadioButton, QObject *ipadressTextField,
                                                   QObject *netmaskTextField, QObject *gatewayTextField, QObject *dnsserverTextField)
{
    setCurrentIpAddressConfig(networkInterfaceComboboxIndex);

    if(ipSettings->DHCPisEnable)
    {
        dynamicIPRadioButton->setProperty("checked", QVariant(true));
        ipadressTextField->setProperty("enabled", QVariant(false));
        netmaskTextField->setProperty("enabled", QVariant(false));
        gatewayTextField->setProperty("enabled", QVariant(false));
        dnsserverTextField->setProperty("enabled", QVariant(false));
    }
    else
    {
        staticIPRadioButton->setProperty("checked", QVariant(true));

        ipadressTextField->setProperty("enabled", QVariant(true));
        netmaskTextField->setProperty("enabled", QVariant(true));
        gatewayTextField->setProperty("enabled", QVariant(true));
        dnsserverTextField->setProperty("enabled", QVariant(true));

        QStringList ipAddressWithMask = ipSettings->ipAddressWithMask.split("/");
        QString ipAddress = ipAddressWithMask[0];


        QString netMask = convertNetMaskToFull(ipAddressWithMask[1]);

        ipadressTextField->setProperty("text", QVariant(ipAddress));
        netmaskTextField->setProperty("text", QVariant(netMask));
        gatewayTextField->setProperty("text", ipSettings->gateway);
        dnsserverTextField->setProperty("text", ipSettings->dns);
    }
}

void SettingsIpAddress::tfIpAddress_onEditingFinished(QString text)
{
    QStringList ipAddressWithMask = ipSettings->ipAddressWithMask.split("/");
    QString netMask = ipAddressWithMask[1];
    QString newIpAddressWithMask = text + "/" + netMask;
    ipSettings->ipAddressWithMask = newIpAddressWithMask;
}

void SettingsIpAddress::rbDynamicIP_onClicked()
{
    ipSettings->DHCPisEnable = true;
}

void SettingsIpAddress::rbStaticIP_onClicked(const QString ipAddressTextField, const QString netmaskTextField, const QString gatewayTextField, const QString dnsserverTextField)
{
    QString ipAddressWithMask = ipAddressTextField + "/" + convertNetMaskToShort(netmaskTextField);
    ipSettings->DHCPisEnable = false;
    ipSettings->ipAddressWithMask = ipAddressWithMask;
    ipSettings->gateway = gatewayTextField;
    ipSettings->dns = dnsserverTextField;
}

void SettingsIpAddress::tfNetMask_onEditingFinished(QString text)
{
    QStringList ipAddressWithMask = ipSettings->ipAddressWithMask.split("/");
    QString ipAddress = ipAddressWithMask[0];
    QString newIpAddressWithMask = ipAddress + "/" + convertNetMaskToShort(text);
    ipSettings->ipAddressWithMask = newIpAddressWithMask;
}

void SettingsIpAddress::tfGateway_onEditingFinished(QString text)
{
    ipSettings->gateway = text;
}

void SettingsIpAddress::tfDNSServer_onEditingFinished(QString text)
{
    ipSettings->dns = text;
}

void SettingsIpAddress::saveIpAddressConfiguration()
{
    QSettings wifiqsettings(WIFI_CONFIG_FILE, QSettings::IniFormat);
    wifiqsettings.clear();
    wifiqsettings.setValue("Match/Name", QVariant("wlan0"));
    if(wifiSettings->DHCPisEnable)
        wifiqsettings.setValue("Network/DHCP", QVariant("yes"));
    else
    {
        wifiqsettings.setValue("Network/Address", QVariant(wifiSettings->ipAddressWithMask));
        wifiqsettings.setValue("Network/Gateway", QVariant(wifiSettings->gateway));
        wifiqsettings.setValue("Network/DNS", QVariant(wifiSettings->dns));
    }
    wifiqsettings.sync();


    QSettings ethqsettings(ETHERNET_CONFIG_FILE, QSettings::IniFormat);
    ethqsettings.clear();
    ethqsettings.setValue("Match/Name", QVariant("eth0"));
    if(ethSettings->DHCPisEnable)
        ethqsettings.setValue("Network/DHCP", QVariant("yes"));
    else
    {
        ethqsettings.setValue("Network/Address", QVariant(ethSettings->ipAddressWithMask));
        ethqsettings.setValue("Network/Gateway", QVariant(ethSettings->gateway));
        ethqsettings.setValue("Network/DNS", QVariant(ethSettings->dns));
    }
    ethqsettings.sync();


    Systemd::restartUnit(Systemd::System, "systemd-networkd", Systemd::Unit::Replace);
}

void SettingsIpAddress::setCurrentIpAddressConfig(const int &networkInterfaceComboboxIndex)
{

    if(networkInterfaceComboboxIndex == 0)
    {
        ipSettings = wifiSettings;
    }
    else
    {
        ipSettings = ethSettings;
    }
}

QString SettingsIpAddress::convertNetMaskToShort(QString decMask)
{
    QString netmask = "";
    QStringList fullMask = decMask.split('.');

    QString binMask = decToBin(fullMask[0]) + decToBin(fullMask[1]) + decToBin(fullMask[2]) + decToBin(fullMask[3]);
    int count = binMask.count(QLatin1Char('1'));

    netmask = QString::number(count);
    return netmask;
}

QString SettingsIpAddress::convertNetMaskToFull(QString decMaskStr)
{
    QString binMask;
    QString netMask;
    int decMask = decMaskStr.toInt();

    for(int i = 0; i < 32; i++)
    {
        if(i < decMask)
            binMask += "1";
        else
        {
            binMask += "0";
        }
    }

    QStringList binMaskList = splitString(binMask, 8);
    netMask = binToDec(binMaskList[0]) + "." + binToDec(binMaskList[1]) + "." + binToDec(binMaskList[2]) + "." + binToDec(binMaskList[3]);

    return netMask;
}

QString SettingsIpAddress::binToDec(QString bin)
{
    int base = 1;
    int temp = bin.toInt();
    int dec_value = 0;

    while(temp)
    {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return QString::number(dec_value);
}

QString SettingsIpAddress::decToBin(QString dec)
{
    std::string bin = std::bitset<8>(dec.toLong()).to_string();
    return QString::fromStdString(bin);
}

QStringList SettingsIpAddress::splitString(const QString &str, int n)
{
    QStringList stringList;

    QString tmp(str);

    while(!tmp.isEmpty())
    {
        stringList.append(tmp.left(n));
        tmp.remove(0, n);
    }

    return stringList;
}
