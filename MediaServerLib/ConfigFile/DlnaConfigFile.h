#ifndef EDITDLNACONFIGFILE_H
#define EDITDLNACONFIGFILE_H

#include "IFileManager.h"
#include "IConfigFile.h"

#include <memory>

class DlnaConfigFile : public IConfigFile
{
public:
    DlnaConfigFile(std::unique_ptr<IFileManager> ptrFileManager);
    bool SaveConfiguration(const VectorData &mConfigsParameters) override;
    bool LoadConfiguration(VectorData &configuration) override;

private:
    std::unique_ptr<IFileManager> fileManager;
};

#endif // EDITDLNACONFIGFILE_H
