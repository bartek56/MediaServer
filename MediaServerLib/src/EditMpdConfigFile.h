#ifndef EDITMPDCONFIGFILE_H
#define EDITMPDCONFIGFILE_H

#include <QString>
#include <memory>


#include "IFileManager.h"
#include "VectorData.h"

class EditMpdConfigFile
{
public:
    EditMpdConfigFile(std::shared_ptr<IFileManager> ptrFileManager);

    bool OpenFile(VectorData& fileData);
    void SaveFile(const VectorData& mConfigs);

private:
    std::shared_ptr<IFileManager> fileManager;
    const QString MPDCONFIG_PATH="/etc/mediaserver/mpd.conf";
};

#endif // EDITMPDCONFIGFILE_H
