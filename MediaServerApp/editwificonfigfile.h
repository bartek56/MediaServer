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
public:
    //EditWifiConfigFile();
    std::vector<WifiConfigsName> OpenFile(QString fileLocation);
    void SaveWifiConfigs(const std::vector<WifiConfigsName> &vWifiConfig);
};

#endif // EDITWIFICONFIGFILE_H
