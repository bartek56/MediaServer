#ifndef EDITDLNACONFIGFILE_H
#define EDITDLNACONFIGFILE_H
#include <map>
#include <vector>
#include <QString>



class EditDlnaConfigFile
{
public:
    //EditDlnaConfigFile();
    std::map<QString, QString>  OpenFile(QString fileLocation);
    void SaveFile(const std::map<QString, QString> &mConfigs);
};

#endif // EDITDLNACONFIGFILE_H
