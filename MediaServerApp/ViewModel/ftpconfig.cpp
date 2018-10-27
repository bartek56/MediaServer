#include "ftpconfig.h"
#include "editftpconfigfile.h"

FtpConfig::FtpConfig(QObject *parent) : QObject(parent)
{

}

void FtpConfig::setUsersComboBox(QObject* obj)
{
    usersCombobox = obj;
    EditFtpConfigFile editFile;
    auto users = editFile.OpenFile("/etc/vsftpd/ftpd.passwd");
    users.push_back("new user..");
    usersCombobox->setProperty("model",QVariant(users));
}


void FtpConfig::cbUser_onDisplayTextChanged(QString text)
{
    qDebug() << text;
}

