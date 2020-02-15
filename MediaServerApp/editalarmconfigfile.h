#ifndef EDITALARMCONFIGFILE_H
#define EDITALARMCONFIGFILE_H

#include <QString>
#include <map>


class EditAlarmConfigFile
{
public:
    EditAlarmConfigFile();
    void SaveConfiguration(const QString &fileLocation, const std::map<QString,QString> &mConfigsParameters);
    std::map<QString,QString> LoadConfiguration(const QString &fileLocation);
};

#endif // EDITSCREENSAVERCONFIGFILE_H
