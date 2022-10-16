#ifndef EDITFTPCONFIGFILE_H
#define EDITFTPCONFIGFILE_H

#include "IFileManager.h"
#include <QString>

struct FtpUser
{
    QString name;
    QString password;
    QString pathToFiles;
    FtpUser(QString const &name, QString const &password, QString const &pathToFiles) : name(name), password(password), pathToFiles(pathToFiles)
    {
    }
};


class FtpConfigFile
{
public:
    QStringList OpenUsersListFile(QString const &fileLocation);
    QString OpenUserPathFile(QString const &fileLocation);

    void DeleteUsersFile(QString const user);
    void AddUser(const QString userName, const QString password);
    void DeleteUser(const QString userName);
    void CreateOrEditUserConfigFile(const QString userName, const QString pathToFile);
};

#endif// EDITFTPCONFIGFILE_H
