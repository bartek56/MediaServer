#ifndef EDITMPDCONFIGFILE_H
#define EDITMPDCONFIGFILE_H

#include "IFileManager.h"
#include "IConfigFile.h"

#include <QString>
#include <memory>

class MpdConfigFile : public IConfigFile
{
public:
    MpdConfigFile(std::shared_ptr<IFileManager> ptrFileManager);

    bool LoadConfiguration(VectorData& fileData) override;
    bool SaveConfiguration(const VectorData& mConfigs) override;

private:
    std::shared_ptr<IFileManager> fileManager;
};

#endif // EDITMPDCONFIGFILE_H
