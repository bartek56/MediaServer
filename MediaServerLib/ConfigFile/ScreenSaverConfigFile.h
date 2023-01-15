#ifndef EDITSCREENSAVERCONFIGFILE_H
#define EDITSCREENSAVERCONFIGFILE_H

#include "IConfigFile.h"
#include "IFileManager.h"

#include <QString>
#include <memory>

class ScreenSaverConfigFile : public IConfigFile
{
public:
    ScreenSaverConfigFile(std::unique_ptr<IFileManager> ptreFileManager);
    bool LoadConfiguration(VectorData &mConfigsParameters) override;
    bool SaveConfiguration(const VectorData& configs) override;
private:
    std::unique_ptr<IFileManager> fileManager;

};

#endif // EDITSCREENSAVERCONFIGFILE_H
