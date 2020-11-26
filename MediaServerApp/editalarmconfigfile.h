#ifndef EDITALARMCONFIGFILE_H
#define EDITALARMCONFIGFILE_H

#include <QString>
#include <map>


class EditAlarmConfigFile
{
public:
    const QString ALARM_SCRIPT="/etc/mediaserver/alarm.sh";
    EditAlarmConfigFile();

    void SaveConfiguration(const std::map<QString,QString> &mConfigsParameters);
    std::map<QString,QString> LoadConfiguration();
};

#endif // EDITSCREENSAVERCONFIGFILE_H
