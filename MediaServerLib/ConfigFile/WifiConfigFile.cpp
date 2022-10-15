#include "WifiConfigFile.h"
#include "IConfigFile.h"

#include <QFile>
#include <QTextStream>

WifiConfigFile::WifiConfigFile(std::shared_ptr<IFileManager> fileManagerPtr) : fileManager(std::move(fileManagerPtr))
{
}

bool WifiConfigFile::LoadConfiguration(VectorData &wifiConfiguration, std::vector<VectorData> &ssidConfiguration)
{
    QString fileData = "";
    bool res = fileManager->read(fileData);
    if(!res)
    {
        return false;
    }

    QStringList lines = fileData.split('\n');
    bool startConfig = false;
    VectorData configsParameters;
    for(int i = 0; i < lines.size(); i++)
    {
        auto line = lines[i];

        // empty line
        if(line.size() < 1)
            continue;

        // global configuration
        if(!startConfig and line.contains('=') and not line.contains('{') and not line.contains('}'))
        {
            auto parameter = line.split('=');
            if(parameter.size() != 2)
                return false;
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            wifiConfiguration.push_back(ConfigData(parameterName, parameterValue));
        }

        if(line.contains('{') and line.contains('}'))
        {
            return false;
        }

        // start ssid config
        else if(line.contains('{'))
        {
            startConfig = true;
        }
        // end ssid config
        else if(line.contains('}'))
        {
            startConfig = false;
            ssidConfiguration.push_back(configsParameters);
            configsParameters.clear();
        }
        else if(startConfig)
        {
            auto parameter = line.split('=');
            if(parameter.size() != 2)
                return false;
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            parameterValue.remove(parameterValue.length() - 1, 1);// remove " on last sign
            parameterValue.remove(0, 1);                          // remove " on first sign
            parameterName.replace(" ", "");

            configsParameters.push_back(ConfigData(parameterName, parameterValue));
        }
    }

    if(ssidConfiguration.empty() and wifiConfiguration.empty())
        return false;
    return true;
}

bool WifiConfigFile::SaveConfiguration(const VectorData &wifiConfiguration, const std::vector<VectorData> &ssidConfigs)
{
    QString dataToFile;

    for(const auto &wifiConfig : wifiConfiguration)
    {
        QString dataLine;
        dataLine = wifiConfig.key + "=" + wifiConfig.value + "\n";
        dataToFile.push_back(dataLine);
    }

    for(const auto &vectorData : ssidConfigs)
    {
        dataToFile.push_back("network={\n");
        for(const auto &data : vectorData)
        {
            QString lineData;
            lineData = data.key + "=\"" + data.value + "\"\n";
            dataToFile.push_back(lineData);
        }
        dataToFile.push_back("}\n");
    }

    bool result = fileManager->save(dataToFile);
    return result;
}

/*
std::vector<WifiConfigsName> WifiConfigFile::OpenFile()
{
    QFile file (WPA_CONFIG_FILE);
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
*/

/*

void WifiConfigFile::SaveWifiConfigs(const std::vector<WifiConfigsName> &vWifiConfigs)
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
*/
