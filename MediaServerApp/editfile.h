#ifndef EDITFILE_H
#define EDITFILE_H

#include <QString>
#include <vector>
#include <map>


struct ConfigsName {
    QString name;
    std::map<QString, QString> configs;
    ConfigsName(QString const & name, std::map<QString, QString> const & configs)
    : name(name), configs(configs) {
    }
};

class EditFile
{
public:
    std::vector<ConfigsName> OpenFile(QString fileLocation);
    void SaveFile(QString fileLocation,std::vector<ConfigsName> vConfigs);

private:
};


#endif // EDITFILE_H
