#include "ftpconfig.h"


FtpConfig::FtpConfig(QObject *parent) : QObject(parent)
{

}

void FtpConfig::tfUser_onEditingFinished(const QString text)
{
    qDebug() << text;
}

void FtpConfig::bAddUser_onClicked(const QString userName, const QString password, const QString catalog)
{
    foreach (const QString &str, users)
    {
        if (str.contains(userName))
        {
            qDebug() << "user exist";
            return;
        }
    }

    for (auto iter=vUserConfig.begin(); iter != vUserConfig.end();++iter)
    {
        auto a = *iter;
        if(a->name==userName)
        {
            qDebug() << "user exist";
            return;
        }
    }
    auto user = std::make_shared<FtpUser>(userName,password,catalog);
    vUserConfig.push_back(std::move(user));
}

void FtpConfig::setUsersComboBox(QObject* obj)
{
    cbUsers = obj;
    QString fileLocation = "/etc/vsftpd/ftpd.passwd";
    users = editFile.OpenUsersListFile(fileLocation);
    cbUsers->setProperty("model",QVariant(users));
}

void FtpConfig::cbUser_onDisplayTextChanged(const QString userName)
{
    QString pathTofile="/etc/vsftpd_user_conf/";
    pathTofile.push_back(userName);
    QString path = editFile.OpenUserPathFile(pathTofile);
    tfPath->setProperty("text",QVariant(path));
}

void FtpConfig::bSave_onClicked()
{
    SaveUsers();
    CreateUserConfigFile();
    QProcess::execute("systemctl restart vsftpd");
}

void FtpConfig::SaveUsers()
{
    for (auto iter=vUserConfig.begin(); iter != vUserConfig.end();++iter)
    {
        auto ftpUser = *iter;
        editFile.AddUser(ftpUser->name,ftpUser->password);
    }
}

void FtpConfig::CreateUserConfigFile()
{
    for (auto iter=vUserConfig.begin(); iter != vUserConfig.end();++iter)
    {
        auto ftpUser = *iter;
        editFile.CreateUserConfigFile(ftpUser->name,ftpUser->pathToFiles);
    }
}

void FtpConfig::setPathTextField(QObject* obj)
{
    tfPath = obj;
}


