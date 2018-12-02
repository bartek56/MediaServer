#ifndef EDITSCREENSAVERCONFIGFILE_H
#define EDITSCREENSAVERCONFIGFILE_H

#include <QString>
#include <map>

class EditScreenSaverConfigFile
{
public:
    EditScreenSaverConfigFile();
    void SaveConfiguration(const QString &fileLocation, const std::map<QString,QString> &mConfigsParameters);
    std::map<QString,QString> LoadConfiguration(const QString &fileLocation);
};

#endif // EDITSCREENSAVERCONFIGFILE_H
