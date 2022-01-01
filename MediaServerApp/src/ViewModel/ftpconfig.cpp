#include "ftpconfig.h"
#include <QtSystemd/unit.h>
#include <QtSystemd/sdmanager.h>

FtpConfig::FtpConfig(QObject *parent) : QObject(parent)
{
}


void FtpConfig::checkService(QObject *saveButton)
{
    const QString unitName("vsftpd.service");
    auto text = Systemd::getUnit(Systemd::User, unitName).data()->activeState();
    saveButton->setProperty("enabled", QVariant(!text.contains("in")));
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
    QString fileLocation = "/etc/vsftpd/ftpd.passwd";
    users = editFile.OpenUsersListFile(fileLocation);
    cbUsers->setProperty("model", QVariant(users));
}

void FtpConfig::cbUser_onDisplayTextChanged(const QString userName)
{

    QString path = getUpdateUserPath(userName);
    if(path == nullptr)
    {
        QString pathTofile = "/etc/vsftpd_user_conf/";
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
    SaveUsers();
    UpdateUsers();
    DeleteUsers();
    Systemd::restartUnit(Systemd::System, "vsftpd.service", Systemd::Unit::Replace);
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
