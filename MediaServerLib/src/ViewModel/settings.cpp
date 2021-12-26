#include "settings.h"

#include <QDebug>
#include <QFile>
#include <map>
#include <bitset>

Settings::Settings(QObject *parent) : QObject(parent)
{
    wifiIpAddressConfigFile = std::make_unique<EditHeadersConfigFile>(WIFI_CONFIG_FILE);
    ethernetIpAddressConfigFile = std::make_unique<EditHeadersConfigFile>(ETHERNET_CONFIG_FILE);
}

void Settings::updateNetworkStatus(QObject *obj)
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("networkctl status");

    while(builder.waitForFinished());

    QString info = builder.readAll();
    obj->setProperty("text",QVariant(info));
}

void Settings::checkTvHeadEndServiceStatus(QObject *statusSwitch, QObject *statusButton)
{
    checkSystemdStatus(statusSwitch, statusButton, TVHEADEND_SERVICE);
}

void Settings::tvHeadEndStatusSwitch_OnClicked(const bool tvHeadEndStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(tvHeadEndStatusSwitchIsChecked, TVHEADEND_SERVICE);
}

void Settings::tvHeadEndStatusButton_OnClicked(QObject *tvHeadEndStatusSwitch, const QString tvHeadEndStatusButton)
{
    StatusButton_onClicked(tvHeadEndStatusSwitch, tvHeadEndStatusButton, TVHEADEND_SERVICE);
}


void Settings::checkYMPDSystemdStatus(QObject *ympdStatusSwitch, QObject *ympdStatusButton)
{
    checkSystemdStatus(ympdStatusSwitch, ympdStatusButton, YMPD_SERVICE);
}

void Settings::ympdStatusSwitch_OnClicked(const bool ympdStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(ympdStatusSwitchIsChecked, YMPD_SERVICE);
}

void Settings::ympdStatusButton_OnClicked(QObject *ympdStatusSwitch, const QString ympdStatusButton)
{
    StatusButton_onClicked(ympdStatusSwitch, ympdStatusButton, YMPD_SERVICE);
}



void Settings::checkMPDSystemdStatus(QObject *mpdStatusSwitch, QObject *mpdStatusButton)
{
     checkSystemdStatus(mpdStatusSwitch, mpdStatusButton, MPD_SERVICE);
}

void Settings::mpdStatusSwitch_OnClicked(const bool mpdStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(mpdStatusSwitchIsChecked, MPD_SERVICE);
}

void Settings::mpdStatusButton_OnClicked(QObject *mpdStatusButton, const QString mpdStatusButtonText)
{
    StatusButton_onClicked(mpdStatusButton, mpdStatusButtonText, MPD_SERVICE);
}


void Settings::checkDLNASystemdStatus(QObject *dlnaStatusSwitch, QObject *dlnaStatusButton)
{
    checkSystemdStatus(dlnaStatusSwitch, dlnaStatusButton, MINIDLNA_SERVICE);
}

void Settings::dlnaStatusSwitch_OnClicked(const bool dlnaStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(dlnaStatusSwitchIsChecked, MINIDLNA_SERVICE);
}

void Settings::dlnaStatusButton_OnClicked(QObject *dlnaStatusButton, const QString dlnaStatusButtonText)
{
    StatusButton_onClicked(dlnaStatusButton, dlnaStatusButtonText, MINIDLNA_SERVICE);
}


void Settings::checkSMBSystemdStatus(QObject *smbStatusSwitch, QObject *smbStatusButton)
{
    checkSystemdStatus(smbStatusSwitch, smbStatusButton, SMB_SERVICE);
}

void Settings::sambaStatusSwitch_OnClicked(const bool sambaStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, SMB_SERVICE);
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, NMB_SERVICE);
}

void Settings::sambaStatusButton_OnClicked(QObject *sambaStatusButton, const QString sambaStatusButtonText)
{
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText, SMB_SERVICE);
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText, NMB_SERVICE);
}



void Settings::checkFTPSystemdStatus(QObject *ftpStatusSwitch, QObject *ftpStatusButton)
{
    checkSystemdStatus(ftpStatusSwitch, ftpStatusButton, VSFTPD_SERVICE);
}

void Settings::ftpStatusSwitch_OnClicked(const bool ftpStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(ftpStatusSwitchIsChecked, VSFTPD_SERVICE);
}

void Settings::ftpStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText)
{
    StatusButton_onClicked(ftpStatusButton, ftpStatusButtonText, VSFTPD_SERVICE);
}



void Settings::checkFileBrowserSystemdStatus(QObject *fileBrowserStatusSwitch, QObject *fileBrowserStatusButton)
{
    checkSystemdStatus(fileBrowserStatusSwitch, fileBrowserStatusButton, FILEBROWSER_SERVICE);
}

void Settings::fileBrowserStatusSwitch_OnClicked(const bool fileBrowserStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(fileBrowserStatusSwitchIsChecked, FILEBROWSER_SERVICE);
}

void Settings::fileBrowserStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText)
{
    StatusButton_onClicked(ftpStatusButton, ftpStatusButtonText, FILEBROWSER_SERVICE);
}



void Settings::checkTorrentClientSystemdStatus(QObject *torrentClientStatusSwitch, QObject *torrentCLientStatusButton)
{
    checkSystemdStatus(torrentClientStatusSwitch, torrentCLientStatusButton, TRANSMISSION_SERVICE);
}

void Settings::torrentClientStatusSwitch_OnClicked(const bool torrentClientStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(torrentClientStatusSwitchIsChecked, TRANSMISSION_SERVICE);
}

void Settings::torrentClientStatusButton_OnClicked(QObject *torrentClientStatusButton, const QString torrentClientStatusButtonText)
{
    StatusButton_onClicked(torrentClientStatusButton, torrentClientStatusButtonText, TRANSMISSION_SERVICE);
}

bool Settings::checkSystemdStatusIsActive(const QString &serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active "+serviceName);
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    return !text.contains("in");
}

bool Settings::checkSystemdStatusIsEnabled(const QString &serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-enabled "+serviceName);
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    return text.contains("enabled");
}

bool Settings::checkSystemdStatusExist(const QString &serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-enabled "+serviceName);
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    return (text.contains("enabled") || text.contains("disabled"));
}

void Settings::checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString nameService)
{
    auto serviceExist = checkSystemdStatusExist(nameService);

    statusButton->setProperty("enabled",QVariant(serviceExist));
    statusSwitch->setProperty("enabled",QVariant(serviceExist));

    if(serviceExist)
    {
      bool serviceIsEnable = checkSystemdStatusIsEnabled(nameService);
      statusSwitch->setProperty("checked",QVariant(serviceIsEnable));
      auto serviceIsActive = checkSystemdStatusIsActive(nameService);

      if(serviceIsActive)
      {
          statusButton->setProperty("text",QVariant("stop"));
      }
      else
      {
          statusButton->setProperty("text",QVariant("start"));
      }
    }
}

void Settings::StatusSwitch_onClicked(const bool statusSwitchIsChecked, const QString &serviceName)
{
    if(statusSwitchIsChecked)
    {
          QProcess::execute("systemctl", QStringList() << "-c" << "is-active vsftpd");
    }
    else
    {
        QProcess::execute("systemctl disable "+serviceName);
    }
}

void Settings::StatusButton_onClicked(QObject *statusButton, const QString statusButtonText, const QString &serviceName)
{
    if(statusButtonText.contains("start"))
    {
        QProcess::execute("systemctl start " + serviceName);
        statusButton->setProperty("text",QVariant("stop"));
    }
    else
    {
        QProcess::execute("systemctl stop " + serviceName);
        statusButton->setProperty("text",QVariant("start"));
    }
}


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


void Settings::updateWifiStatus(QObject *obj)
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("iw dev wlan0 link");

    while(builder.waitForFinished());

    QString info = builder.readAll();
    obj->setProperty("text",QVariant(info));

}

void Settings::searchNetworks(QObject* obj)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "iw wlan0 scan | egrep 'SSID|freq|signal|capability'");

    process.setReadChannel(QProcess::StandardOutput);
    QStringList networksList;
    while(process.waitForFinished());
    while (process.canReadLine())
    {
       auto line = process.readLine();
       std::string strLine(line);
       if (strLine.find("SSID")!=std::string::npos)
       {
           auto lineList = line.split(':');
           auto networkName = lineList[1];
           networkName=networkName.remove(0,1);
           networkName=networkName.remove(networkName.length()-1,1);
           std::string strNetworkName(networkName);
           QString qstrNetworkName = QString::fromStdString(strNetworkName);
           networksList.push_back(qstrNetworkName);
       }
    }
    obj->setProperty("model",QVariant(networksList));
}

void Settings::connect(const QString networkName,const QString password)
{
    bool networkExist=false;
    for (auto iter=vWifiConfigs.begin(); iter != vWifiConfigs.end();++iter)
    {
        auto &mConfigs = iter->configs;
        if(mConfigs.at("ssid")==networkName)
        {
            mConfigs.at("psk")=password;
            networkExist=true;
            break;
        }
    }

    if(!networkExist)
    {
        std::vector<WifiConfigsName> vConfigsName;
        std::map<QString, QString> mConfigsParameters;
        mConfigsParameters.insert(std::make_pair("ssid", networkName));
        mConfigsParameters.insert(std::make_pair("psk", password));
        vWifiConfigs.push_back(WifiConfigsName(mConfigsParameters));
    }

    editWifiConfigFile.SaveWifiConfigs(vWifiConfigs);
    QProcess::execute("systemctl restart " + WPASUPPLICANT_SERVICE);
}

void Settings::cbNetworks_onDisplayTextChanged(QString networkName, QObject *obj)
{

    QProcess process;
    QString commend = "iw wlan0 scan | egrep 'SSID|freq|signal|capability' | egrep -B1 '";
    commend.push_back(networkName);
    commend.push_back("'");
    process.start("bash", QStringList() << "-c" << commend);

    QStringList networksList;
    while(process.waitForFinished());

    obj->setProperty("text",QVariant(process.readAll()));
}

void Settings::sWifiOn_OnCheckedChanged(bool wifiOnSwitch)
{
    if(wifiOnSwitch)
    {
        QProcess::execute("ifconfig wlan0 up");
    }
    else if(!wifiOnSwitch)
    {
        QProcess::execute("ifconfig wlan0 down");
    }
}

void Settings::checkWifi(QObject *obj)
{
    QProcess process;
    process.start("iw wlan0 info");

    QStringList networksList;
    while(process.waitForFinished());


    auto line = process.readAll();
    std::string strLine(line);
    if (strLine.find("txpower")!=std::string::npos)
    {
        wifiIsOn=true;
        obj->setProperty("checked",QVariant("true"));
    }
    else
    {
        wifiIsOn=false;
        obj->setProperty("checked",QVariant("false"));
    }
}

void Settings::loadWifiConfigFile()
{
    vWifiConfigs = editWifiConfigFile.OpenFile();
}
