#ifndef MPDCONFIGFILE_H
#define MPDCONFIGFILE_H

#include <map>
#include <QString>
#include <memory>

#include "IFileManager.h"

class MpdConfigFile : public IFileManager
{
public:
    bool read(QString &fileData) override;
    bool save(const QString fileData) override;
private:
    const QString fileName = "/etc/mediaserver/mpd.conf";
};

#endif // MPDCONFIGFILE_H
