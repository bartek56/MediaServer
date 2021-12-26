#ifndef EDITHEADERSCONFIGFILE_H
#define EDITHEADERSCONFIGFILE_H

#include <QString>
#include <map>
#include <vector>

struct HeadersConfig {
    QString name;
    std::map<QString, QString> configs;
    HeadersConfig(QString const &name, std::map<QString, QString> const &configs)
    : name(name), configs(configs) {
    }
};


class EditHeadersConfigFile
{
public:
    EditHeadersConfigFile(const QString &fileLocation)
        : CONFIG_FILE(fileLocation){}

    std::vector<HeadersConfig> OpenFile();
    void SaveFile(std::vector<HeadersConfig> vConfigs);

private:
    QString CONFIG_FILE;

};

#endif // EDITHEADERSCONFIGFILE_H
