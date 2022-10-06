#include "EditWifiConfigFile.h"
#include <QFile>
#include <QTextStream>

std::vector<WifiConfigsName> EditWifiConfigFile::OpenFile()
{
    QFile file (WIFI_CONFIG_FILE);
    std::vector<WifiConfigsName> vConfigsName;
    std::map<QString, QString> mConfigsParameters;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return vConfigsName;

    QByteArray parameterName;

    bool startConfig=false;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        std::string strLine(line);

        if(strLine.find('}')!=std::string::npos)
        {
            startConfig=false;
            vConfigsName.push_back(WifiConfigsName(mConfigsParameters));
            mConfigsParameters.clear();
        }

        if(startConfig)
        {
            auto parameter = line.split('=');
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            parameterValue.remove(parameterValue.length()-2,2); // remove " and \n on last sign
            parameterValue.remove(0,1); // remove " on first sign
            parameterName.replace(" ","");

            mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
        }

        if(strLine.find('{')!=std::string::npos)
        {
            startConfig=true;
        }
    }

    return vConfigsName;
}

void EditWifiConfigFile::SaveWifiConfigs(const std::vector<WifiConfigsName> &vWifiConfigs)
{
    QFile file(WIFI_CONFIG_FILE);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    out << "ctrl_interface=/var/run/wpa_supplicant\n";
    out << "ap_scan=1\n";

    for (auto it = std::begin(vWifiConfigs); it!=std::end(vWifiConfigs); ++it)
    {
        out << "network={\n";
        auto configMap = it->configs;
        for (std::map<QString, QString>::iterator it2=configMap.begin(); it2!=configMap.end(); ++it2)
        {
            out << it2->first << "=\"" << it2->second << "\"\n";
        }
        out << "}\n";
    }
    file.close();
}
