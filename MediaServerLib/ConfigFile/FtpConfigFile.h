#ifndef EDITFTPCONFIGFILE_H
#define EDITFTPCONFIGFILE_H

#include <QString>
#include <vector>
#include <map>
#include <memory>

struct FtpUser {
    QString name;
    QString password;
    QString pathToFiles;
    FtpUser(QString const &name,QString const &password,QString const &pathToFiles)
    : name(name),password(password), pathToFiles(pathToFiles) {
    }
};


class FtpConfigFile
{
public:
    QStringList OpenUsersListFile(QString const &fileLocation);
    QString OpenUserPathFile(QString const &fileLocation);

    void SaveInfile(std::vector<std::shared_ptr<FtpUser>> vUserConfig, QString file);
    void DeleteUsersFile(QString const user);
    void AddUser(const QString userName, const QString password);
    void DeleteUser(const QString userName);
    void CreateOrEditUserConfigFile(const QString userName, const QString pathToFile);

private:
    //FtpUser ftpUser;
};

#endif // EDITFTPCONFIGFILE_H
