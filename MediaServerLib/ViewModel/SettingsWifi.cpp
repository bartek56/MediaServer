#include "SettingsWifi.h"
#include "ConfigFile/ConfigFile.h"

#include <QDebug>
#include <QtSystemd/sdmanager.h>
#include <QtSystemd/unit.h>
#include <bitset>
#include <memory>


SettingsWifi::SettingsWifi(QObject *parent) : QObject(parent), wifiConfigFile(std::make_shared<ConfigFile>(WPA_CONFIG_FILE))
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("iw", QStringList() << "wlan0"
                                      << "info");

    while(builder.waitForFinished())
        ;

    QString info = builder.readAll();
    if(info.contains("command not found"))
    {
        infoMessage = "iw tools not exist - network manager not support";
        qCritical("command iw not exist");
        isIWSupported = false;
    }
    else if(info.contains("iw [options] command"))
    {
        qCritical("interface wlan0 not exist");
        infoMessage = "interface wlan0 not exist";
        isIWSupported = false;
    }
    else if(info.contains("Intercae wlan0"))
    {
        qDebug() << "iw is supported";
        isIWSupported = true;
    }
    else
    {
        isIWSupported = false;
        infoMessage = "unknown result of iw tool";
        qCritical("unknown result of iw tool");
    }
}

bool SettingsWifi::iwExist()
{
    return isIWSupported;
}

QString SettingsWifi::getMessage()
{
    return infoMessage;
}

void SettingsWifi::updateWifiStatus(QObject *obj)
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("iw", QStringList() << "dev"
                                      << "wlan0"
                                      << "link");

    while(builder.waitForFinished())
        ;

    QString info = builder.readAll();
    obj->setProperty("text", QVariant(info));
}

void SettingsWifi::searchNetworks(QObject *obj)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c"
                                        << "iw wlan0 scan | egrep 'SSID|freq|signal|capability'");

    process.setReadChannel(QProcess::StandardOutput);
    QStringList networksList;
    while(process.waitForFinished())
        ;
    while(process.canReadLine())
    {
        auto line = process.readLine();
        std::string strLine(line);
        if(strLine.find("SSID") != std::string::npos)
        {
            auto lineList = line.split(':');
            auto networkName = lineList[1];
            networkName = networkName.remove(0, 1);
            networkName = networkName.remove(networkName.length() - 1, 1);
            std::string strNetworkName(networkName);
            QString qstrNetworkName = QString::fromStdString(strNetworkName);
            networksList.push_back(qstrNetworkName);
        }
    }
    obj->setProperty("model", QVariant(networksList));
}

void SettingsWifi::connect(const QString networkName, const QString password)
{
    bool networkExist = false;
    for(auto iter = vSsidConfig.begin(); iter != vSsidConfig.end(); ++iter)
    {
        if(iter->getValueByKey("ssid") == networkName)
        {
            iter->setValueByKey("psk", password);
            networkExist = true;
            break;
        }
    }

    if(!networkExist)
    {
        VectorData wifiConfigs;
        wifiConfigs.push_back(ConfigData("ssid", networkName));
        wifiConfigs.push_back(ConfigData("psk", password));
        vSsidConfig.push_back(wifiConfigs);
    }

    bool result = wifiConfigFile.SaveConfiguration(wifiConfigs, vSsidConfig);
    if(!result)
        qCritical("Failed to save Wifi user and password configuration");

    Systemd::restartUnit(Systemd::System, WPASUPPLICANT_SERVICE, Systemd::Unit::Replace);
}

void SettingsWifi::cbNetworks_onDisplayTextChanged(QString networkName, QObject *obj)
{
    QProcess process;
    QString commend = "iw wlan0 scan | egrep 'SSID|freq|signal|capability' | egrep -B1 '";
    commend.push_back(networkName);
    commend.push_back("'");
    process.start("bash", QStringList() << "-c" << commend);

    QStringList networksList;
    while(process.waitForFinished())
        ;

    obj->setProperty("text", QVariant(process.readAll()));
}

void SettingsWifi::sWifiOn_OnCheckedChanged(bool wifiOnSwitch)
{
    if(wifiOnSwitch)
    {
        QProcess::execute("ifconfig", QStringList() << "wlan0"
                                                    << "up");
        QProcess::execute("systemctl", QStringList() << "start"
                                                     << "wpa_supplicant");
        QProcess::execute("systemctl", QStringList() << "enable"
                                                     << "wpa_supplicant");
    }
    else if(!wifiOnSwitch)
    {
        QProcess::execute("ifconfig", QStringList() << "wlan0"
                                                    << "down");
        QProcess::execute("systemctl", QStringList() << "stop"
                                                     << "wpa_supplicant");
        QProcess::execute("systemctl", QStringList() << "disable"
                                                     << "wpa_supplicant");
    }
}

void SettingsWifi::checkWifi(QObject *obj)
{
    QProcess process;
    process.start("iw", QStringList() << "wlan0"
                                      << "info");

    QStringList networksList;
    while(process.waitForFinished())
        ;

    auto line = process.readAll();
    std::string strLine(line);
    if(strLine.find("txpower") != std::string::npos)
    {
        wifiIsOn = true;
        obj->setProperty("checked", QVariant("true"));
    }
    else
    {
        wifiIsOn = false;
        obj->setProperty("checked", QVariant("false"));
    }
}

void SettingsWifi::loadWifiConfigFile()
{
    if(isIWSupported)
    {
        if(!wifiConfigFile.LoadConfiguration(wifiConfigs, vSsidConfig))
        {
            qCritical("Failed to load wifi configuration");
            infoMessage = "Failed to load wifi configuration";
            isIWSupported = false;
        }
    }
}
