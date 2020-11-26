#ifndef EDITMPDCONFIGFILE_H
#define EDITMPDCONFIGFILE_H

#include <map>
#include <QString>

class EditMpdConfigFile
{
private:
    const QString MPDCONFIG_PATH="/etc/mediaserver/mpd.conf";
public:
    std::map<QString, QString> OpenFile();
    void SaveFile(const std::map<QString, QString> &mConfigs);
};

#endif // EDITMPDCONFIGFILE_H
