#ifndef EDITSAMBACONFIGFILE_H
#define EDITSAMBACONFIGFILE_H

#include <vector>
#include <QString>
#include <map>


struct SambaConfigsName {
    QString name;
    std::map<QString, QString> configs;
    SambaConfigsName(QString const &name, std::map<QString, QString> const &configs)
    : name(name), configs(configs) {
    }
};

class EditSambaConfigFile
{
public:
    std::vector<SambaConfigsName> OpenFile(const QString &fileLocation);
    void SaveFile(QString fileLocation,std::vector<SambaConfigsName> vConfigs);

private:
};


#endif // EDITFILE_H
