#include "settings.h"
#include <bitset>

void Settings::loadIpAddressConfiguration(const int networkInterfaceComboboxIndex, QObject *dynamicIPRadioButton,
                                          QObject *staticIPRadioButton, QObject *ipadressTextField,
                                          QObject *netmaskTextField, QObject *gatewayTextField,
                                          QObject *dnsserverTextField)
{
   setCurrentIpAddressConfig(networkInterfaceComboboxIndex);

   if(vIpAddressConfigsPtr->back().configs.find("DHCP") != vIpAddressConfigsPtr->back().configs.end())
   {
       if(vIpAddressConfigsPtr->back().configs.at("DHCP") == "yes")
       {
           dynamicIPRadioButton->setProperty("checked", QVariant(true));

           ipadressTextField->setProperty("enabled", QVariant(false));
           netmaskTextField->setProperty("enabled", QVariant(false));
           gatewayTextField->setProperty("enabled", QVariant(false));
           dnsserverTextField->setProperty("enabled", QVariant(false));
       }
   }
   else
   {
       staticIPRadioButton->setProperty("checked", QVariant(true));

       ipadressTextField->setProperty("enabled", QVariant(true));
       netmaskTextField->setProperty("enabled", QVariant(true));
       gatewayTextField->setProperty("enabled", QVariant(true));
       dnsserverTextField->setProperty("enabled", QVariant(true));

       QStringList ipAddressWithMask = vIpAddressConfigsPtr->back().configs.at("Address").split("/");
       QString ipAddress = ipAddressWithMask[0];

       QString netMask = convertNetMaskToFull(ipAddressWithMask[1]);

       ipadressTextField->setProperty("text", QVariant(ipAddress));
       netmaskTextField->setProperty("text", QVariant(netMask));
       gatewayTextField->setProperty("text", QVariant(vIpAddressConfigsPtr->back().configs.at("Gateway")));
       dnsserverTextField->setProperty("text", QVariant(vIpAddressConfigsPtr->back().configs.at("DNS")));
   }
}

void Settings::tfIpAddress_onEditingFinished(QString text)
{
    QStringList ipAddressWithMask = vIpAddressConfigsPtr->back().configs.at("Address").split("/");
    QString netMask = ipAddressWithMask[1];
    QString newIpAddressWithMask = text+"/"+netMask;
    vIpAddressConfigsPtr->back().configs.at("Address")=newIpAddressWithMask;
}

void Settings::rbDynamicIP_onClicked()
{
    vIpAddressConfigsPtr->back().configs.clear();
    vIpAddressConfigsPtr->back().configs.clear();
    vIpAddressConfigsPtr->back().configs.insert(std::make_pair("DHCP","yes"));
}

void Settings::rbStaticIP_onClicked(const QString ipAddressTextField, const QString netmaskTextField, const QString gatewayTextField, const QString dnsserverTextField)
{
    QString ipAddressWithMask = ipAddressTextField+"/"+convertNetMaskToShort(netmaskTextField);

    vIpAddressConfigsPtr->back().configs.clear();
    vIpAddressConfigsPtr->back().configs.insert(std::make_pair("Address",ipAddressWithMask));
    vIpAddressConfigsPtr->back().configs.insert(std::make_pair("Gateway",gatewayTextField));
    vIpAddressConfigsPtr->back().configs.insert(std::make_pair("DNS",dnsserverTextField));
}

void Settings::tfNetMask_onEditingFinished(QString text)
{
    QStringList ipAddressWithMask = vIpAddressConfigsPtr->back().configs.at("Address").split("/");
    QString ipAddress = ipAddressWithMask[0];
    QString newIpAddressWithMask = ipAddress+"/"+convertNetMaskToShort(text);
    vIpAddressConfigsPtr->back().configs.at("Address")=newIpAddressWithMask;
}

void Settings::tfGateway_onEditingFinished(QString text)
{
    vIpAddressConfigsPtr->back().configs.at("Gateway")=text;
}

void Settings::tfDNSServer_onEditingFinished(QString text)
{
    vIpAddressConfigsPtr->back().configs.at("DNS")=text;
}

void Settings::saveIpAddressConfiguration()
{
    if(vWifiIpAddressConfigsPtr != nullptr)
        wifiIpAddressConfigFile->SaveFile(*vWifiIpAddressConfigsPtr.get());
    if(vEtnernetIpAddressConfigsPtr != nullptr)
        ethernetIpAddressConfigFile->SaveFile(*vEtnernetIpAddressConfigsPtr.get());

    QProcess::execute("systemctl restart systemd-networkd");
}

void Settings::setCurrentIpAddressConfig(const int &networkInterfaceComboboxIndex)
{
    if(networkInterfaceComboboxIndex==0)
    {
        if(vWifiIpAddressConfigsPtr == nullptr)
        {
            vWifiIpAddressConfigsPtr = std::make_shared< std::vector<HeadersConfig> >(std::move( wifiIpAddressConfigFile->OpenFile() ));
        }
        vIpAddressConfigsPtr = vWifiIpAddressConfigsPtr;
    }
    else
    {
        if(vEtnernetIpAddressConfigsPtr == nullptr)
        {
            vEtnernetIpAddressConfigsPtr = std::make_shared<std::vector<HeadersConfig>>(std::move(ethernetIpAddressConfigFile->OpenFile()));
        }
        vIpAddressConfigsPtr = vEtnernetIpAddressConfigsPtr;
    }
}

QString Settings::convertNetMaskToShort(QString decMask)
{
    QString netmask = "";
    QStringList fullMask = decMask.split('.');

    QString binMask = decToBin(fullMask[0]) + decToBin(fullMask[1]) + decToBin(fullMask[2]) + decToBin(fullMask[3]);
    int count = binMask.count(QLatin1Char('1'));

    netmask=QString::number(count);
    return netmask;
}

QString Settings::convertNetMaskToFull(QString decMaskStr)
{
    QString binMask;
    QString netMask;
    int decMask = decMaskStr.toInt();

    for(int i=0; i<32;i++)
    {
        if(i<decMask)
            binMask+="1";
        else {
            binMask+="0";
        }
    }

    QStringList binMaskList = splitString(binMask,8);
    netMask = binToDec(binMaskList[0]) + "." + binToDec(binMaskList[1]) + "." + binToDec(binMaskList[2]) + "." + binToDec(binMaskList[3]);

    return netMask;
}

QString Settings::binToDec(QString bin)
{
    int base=1;
    int temp = bin.toInt();
    int dec_value=0;

    while (temp)
    {
        int last_digit = temp%10;
        temp = temp/10;
        dec_value += last_digit * base;
        base=base*2;
    }
    return QString::number(dec_value);
}

QString Settings::decToBin(QString dec)
{
    std::string bin = std::bitset<8>(dec.toLong()).to_string();
    return QString::fromStdString(bin);
}

QStringList Settings::splitString(const QString &str, int n)
{
    QStringList stringList;

    QString tmp(str);

    while (!tmp.isEmpty()) {
        stringList.append(tmp.left(n));
        tmp.remove(0, n);
    }

    return stringList;
}

