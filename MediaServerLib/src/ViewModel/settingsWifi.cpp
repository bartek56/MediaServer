#include "settingsWifi.h"

#include <QDebug>
#include <QFile>
#include <QtSystemd/sdmanager.h>
#include <QtSystemd/unit.h>
#include <bitset>
#include <map>

SettingsWifi::SettingsWifi(QObject *parent) : QObject(parent)
{
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
    for(auto iter = vWifiConfigs.begin(); iter != vWifiConfigs.end(); ++iter)
    {
        auto &mConfigs = iter->configs;
        if(mConfigs.at("ssid") == networkName)
        {
            mConfigs.at("psk") = password;
            networkExist = true;
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
    }
    else if(!wifiOnSwitch)
    {
        QProcess::execute("ifconfig", QStringList() << "wlan0"
                                                    << "down");
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
    vWifiConfigs = editWifiConfigFile.OpenFile();
}
