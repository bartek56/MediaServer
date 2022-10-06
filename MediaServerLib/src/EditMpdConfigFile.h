#ifndef EDITMPDCONFIGFILE_H
#define EDITMPDCONFIGFILE_H

#include <unordered_map>
#include <QString>
#include <memory>

#include "IFileManager.h"

class EditMpdConfigFile
{
private:
    const QString MPDCONFIG_PATH="/etc/mediaserver/mpd.conf";
    std::shared_ptr<IFileManager> fileManager;
public:
    EditMpdConfigFile(std::shared_ptr<IFileManager> ptrFileManager);
    bool OpenFile(std::unordered_map<QString, QString>& fileData);

    void SaveFile(const std::unordered_map<QString, QString> &mConfigs);
};

#endif // EDITMPDCONFIGFILE_H
