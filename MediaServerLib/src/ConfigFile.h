#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <map>
#include <QString>
#include <memory>

#include "IFileManager.h"

class ConfigFile : public IFileManager
{
public:
    ConfigFile(const QString configFile);
    bool read(QString &fileData) override;
    bool save(const QString fileData) override;
    QString fileName;
};

#endif // MPDCONFIGFILE_H
