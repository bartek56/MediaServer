#ifndef EDITALARMCONFIGFILE_H
#define EDITALARMCONFIGFILE_H

#include "IFileManager.h"
#include "IConfigFile.h"

#include "../Utils/VectorData.h"

#include <QString>
#include <memory>
#include <unordered_map>

class AlarmConfigFile : public IConfigFile
{
public:

  AlarmConfigFile(std::shared_ptr<IFileManager> ptrFileManager);

  bool SaveConfiguration(const VectorData &mConfigsParameters) override;
  bool LoadConfiguration(VectorData &configuration) override;

private:
  std::shared_ptr<IFileManager> fileManager;
};

#endif // EDITALARMCONFIGFILE_H
