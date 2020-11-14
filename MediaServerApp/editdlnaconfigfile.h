#ifndef EDITDLNACONFIGFILE_H
#define EDITDLNACONFIGFILE_H
#include <map>
#include <vector>
#include <QString>



class EditDlnaConfigFile
{
private:
    const QString DLNA_CONFIG = "/etc/minidlna.conf";
public:
    //EditDlnaConfigFile();
    std::map<QString, QString>  OpenFile();
    void SaveFile(const std::map<QString, QString> &mConfigs);
};

#endif // EDITDLNACONFIGFILE_H
