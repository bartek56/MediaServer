
#pragma once

#include <string>
#include <QString>
#include <map>

class IFileManager {
public:
    virtual bool read(QString& data) = 0;
    virtual bool save(const QString dataToSave) = 0;
    virtual ~IFileManager() = default;
};
