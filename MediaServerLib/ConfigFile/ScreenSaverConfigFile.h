#ifndef EDITSCREENSAVERCONFIGFILE_H
#define EDITSCREENSAVERCONFIGFILE_H

#include <QString>
#include <map>

class ScreenSaverConfigFile
{
private:
    QString fileLocation = "/etc/mediaserver/screensaver.conf";

public:
    void SaveConfiguration(const std::map<QString,QString> &mConfigsParameters);
    std::map<QString,QString> LoadConfiguration();
};

#endif // EDITSCREENSAVERCONFIGFILE_H
