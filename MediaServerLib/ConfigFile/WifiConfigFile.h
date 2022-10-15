#ifndef EDITWIFICONFIGFILE_H
#define EDITWIFICONFIGFILE_H

#include "IConfigFile.h"
#include "IFileManager.h"
#include <memory>

class WifiConfigFile
{
public:
    WifiConfigFile(std::shared_ptr<IFileManager> ptreFileManager);
    bool LoadConfiguration(VectorData &wifiConfiguration, std::vector<VectorData> &ssidConfiguration);
    bool SaveConfiguration(const VectorData &wifiConfiguration, const std::vector<VectorData> &ssidConfigs);

private:
    std::shared_ptr<IFileManager> fileManager;
};

#endif// EDITWIFICONFIGFILE_H
