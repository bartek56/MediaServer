#ifndef EDITALARMCONFIGFILE_H
#define EDITALARMCONFIGFILE_H

#include "IConfigFile.h"
#include "Utils/VectorData.h"

#include <QString>

class AlarmConfigFile : public IConfigFile
{
public:
    explicit AlarmConfigFile(const QString &configFilePath);

    bool SaveConfiguration(const VectorData &mConfigsParameters) override;
    bool LoadConfiguration(VectorData &configuration) override;

private:
    QString filePath;
};

#endif// EDITALARMCONFIGFILE_H
