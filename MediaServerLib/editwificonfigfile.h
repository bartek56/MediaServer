#ifndef EDITWIFICONFIGFILE_H
#define EDITWIFICONFIGFILE_H

#include <QString>
#include <vector>
#include <map>


struct WifiConfigsName {
    std::map<QString, QString> configs;
    WifiConfigsName(const std::map<QString, QString>  &configs)
    : configs(configs) {
    }
};


class EditWifiConfigFile
{
private:
   const QString WIFI_CONFIG_FILE="/etc/mediaserver/wpa_supplicant.conf";

public:
    //EditWifiConfigFile();
    std::vector<WifiConfigsName> OpenFile();
    void SaveWifiConfigs(const std::vector<WifiConfigsName> &vWifiConfig);
};

#endif // EDITWIFICONFIGFILE_H
