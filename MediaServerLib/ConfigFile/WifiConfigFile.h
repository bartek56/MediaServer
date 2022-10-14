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


class WifiConfigFile
{
private:

public:
    //WifiConfigFile();
    std::vector<WifiConfigsName> OpenFile();
    void SaveWifiConfigs(const std::vector<WifiConfigsName> &vWifiConfig);
};

#endif // EDITWIFICONFIGFILE_H
