#ifndef EDITMPDCONFIGFILE_H
#define EDITMPDCONFIGFILE_H

#include <map>
#include <QString>

class EditMpdConfigFile
{
public:
    std::map<QString, QString> OpenFile(QString fileLocation);
    void SaveFile(const std::map<QString, QString> &mConfigs);
};

#endif // EDITMPDCONFIGFILE_H
