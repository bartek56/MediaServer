#ifndef EDITMPDCONFIGFILE_H
#define EDITMPDCONFIGFILE_H

#include <QString>
#include <memory>


#include "IFileManager.h"
#include "../Utils/VectorData.h"

class MpdConfigFile
{
public:
    MpdConfigFile(std::shared_ptr<IFileManager> ptrFileManager);

    bool OpenFile(VectorData& fileData);
    void SaveFile(const VectorData& mConfigs);

private:
    std::shared_ptr<IFileManager> fileManager;
    const QString MPDCONFIG_PATH="/etc/mediaserver/mpd.conf";
};

#endif // EDITMPDCONFIGFILE_H
