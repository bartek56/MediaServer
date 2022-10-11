#ifndef EDITALARMCONFIGFILE_H
#define EDITALARMCONFIGFILE_H

#include <QString>
#include <memory>
#include <unordered_map>

#include "VectorData.h"
#include "IFileManager.h"

class EditAlarmConfigFile {
public:

  EditAlarmConfigFile(std::shared_ptr<IFileManager> ptrFileManager);

  bool SaveConfiguration(const VectorData &mConfigsParameters);
  bool LoadConfiguration(VectorData &configuration);

private:
  std::shared_ptr<IFileManager> fileManager;
  const QString ALARM_SCRIPT = "/etc/mediaserver/alarm.sh";
};

#endif // EDITALARMCONFIGFILE_H