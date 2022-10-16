#include "FtpConfig.h"
#include <QtSystemd/unit.h>
#include <QtSystemd/sdmanager.h>

FtpConfig::FtpConfig(QObject *parent) : QObject(parent)
{
    auto state = Systemd::getUnitFileState(Systemd::System, FTP_SERVICE);

    if(!QFile(VSFTPD_USERS_CONFIG_FILE).exists())
    {
        configFilesExist = true;
    }
    else
    {
        configFilesExist = false;
        qCritical("VSFTPD config file not exist");
    }

    if(state.contains("able"))
        serviceExist = true;
    else
    {
        serviceExist = false;
        qWarning() << "ftp systemd not support";
    }
}


void FtpConfig::checkService(QObject *saveButton)
{
    if(serviceExist)
    {
        auto text = Systemd::getUnit(Systemd::System, FTP_SERVICE).data()->activeState();
        saveButton->setProperty("enabled", QVariant(!text.contains("in")));
    }
}


void FtpConfig::tfUser_onEditingFinished(const QString text)
{
    qDebug() << text;
}

void FtpConfig::bRemoveUser_onClick(const QString userName)
{
    auto user = std::make_shared<QString>(userName);
    vRemoveUsersConfig.push_back(user);
    users.removeOne(userName);
    cbUsers->setProperty("model", QVariant(users));
}

void FtpConfig::bUpdateUser_onClick(const QString userName, const QString path)
{
    auto user = std::make_shared<FtpUser>(userName, "p", path);
    vUpdateUsersConfig.push_back(std::move(user));
}

void FtpConfig::bAddUser_onClicked(const QString userName, const QString password, const QString catalog)
{
    foreach(const QString &str, users)
    {
        if(str.contains(userName))
            return;
    }

    for(auto iter = vNewUsersConfig.begin(); iter != vNewUsersConfig.end(); ++iter)
    {
        auto a = *iter;
        if(a->name == userName)
            return;
    }

    auto user = std::make_shared<FtpUser>(userName, password, catalog);
    vNewUsersConfig.push_back(std::move(user));
    users.push_back(userName);
    cbUsers->setProperty("model", QVariant(users));
}

void FtpConfig::setUsersComboBox(QObject *obj)
{
    cbUsers = obj;
    auto fileLocation = QString(VSFTPD_USERS_CONFIG_FILE);
    users = editFile.OpenUsersListFile(fileLocation);
    cbUsers->setProperty("model", QVariant(users));
}

void FtpConfig::cbUser_onDisplayTextChanged(const QString userName)
{
    QString path = getUpdateUserPath(userName);
    if(path == nullptr)
    {
        auto pathTofile = QString(VSFTPD_USER_CONF_PATH);
        pathTofile.push_back(userName);
        path = editFile.OpenUserPathFile(pathTofile);
        if(path.size() < 2)
        {
            path = getNewUserPath(userName);
        }
    }
    tfPath1->setProperty("text", QVariant(path));
}

void FtpConfig::bFileDialog1_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    tfPath1->setProperty("text", QVariant(path));
}

void FtpConfig::bFileDialog2_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    tfPath2->setProperty("text", QVariant(path));
}

QString FtpConfig::getUpdateUserPath(const QString &userName)
{
    for(auto iter = vUpdateUsersConfig.begin(); iter != vUpdateUsersConfig.end(); ++iter)
    {
        auto ftpUser = *iter;
        if(ftpUser->name == userName)
        {
            return ftpUser->pathToFiles;
        }
    }
    return nullptr;
}

QString FtpConfig::getNewUserPath(const QString &userName)
{
    for(auto iter = vNewUsersConfig.begin(); iter != vNewUsersConfig.end(); ++iter)
    {
        auto ftpUser = *iter;
        if(ftpUser->name == userName)
        {
            return ftpUser->pathToFiles;
        }
    }
    return nullptr;
}

void FtpConfig::bSave_onClicked()
{
    if(configFilesExist)
    {
        SaveUsers();
        UpdateUsers();
        DeleteUsers();
    }
    if(serviceExist)
        Systemd::restartUnit(Systemd::System, FTP_SERVICE, Systemd::Unit::Replace);
}

void FtpConfig::SaveUsers()
{
    for(auto iter = vNewUsersConfig.begin(); iter != vNewUsersConfig.end(); ++iter)
    {
        auto ftpUser = *iter;
        editFile.AddUser(ftpUser->name, ftpUser->password);
        editFile.CreateOrEditUserConfigFile(ftpUser->name, ftpUser->pathToFiles);
    }
    vNewUsersConfig.clear();
}

void FtpConfig::DeleteUsers()
{
    for(auto iter = vRemoveUsersConfig.begin(); iter != vRemoveUsersConfig.end(); ++iter)
    {
        auto removeFtpUser = *iter;
        editFile.DeleteUser(*removeFtpUser);
        editFile.DeleteUsersFile(*removeFtpUser);
    }
    vRemoveUsersConfig.clear();
}

void FtpConfig::UpdateUsers()
{
    for(auto iter = vUpdateUsersConfig.begin(); iter != vUpdateUsersConfig.end(); ++iter)
    {
        auto ftpUser = *iter;
        editFile.CreateOrEditUserConfigFile(ftpUser->name, ftpUser->pathToFiles);
    }
    vUpdateUsersConfig.clear();
}

void FtpConfig::setPathTextField1(QObject *obj)
{
    tfPath1 = obj;
}
void FtpConfig::setPathTextField2(QObject *obj)
{
    tfPath2 = obj;
}
