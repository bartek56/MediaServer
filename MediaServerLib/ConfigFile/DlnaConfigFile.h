#ifndef EDITDLNACONFIGFILE_H
#define EDITDLNACONFIGFILE_H
#include <map>
#include <vector>
#include <QString>


class DlnaConfigFile
{
private:
    const QString DLNA_CONFIG = "/etc/mediaserver/minidlna.conf";
public:
    //DlnaConfigFile();
    std::map<QString, QString>  OpenFile();
    void SaveFile(const std::map<QString, QString> &mConfigs);
};

#endif // EDITDLNACONFIGFILE_H
