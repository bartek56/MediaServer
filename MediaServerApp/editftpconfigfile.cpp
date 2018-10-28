#include "editftpconfigfile.h"

#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QDebug>

QStringList EditFtpConfigFile::OpenUsersListFile(const QString &fileLocation)
{
    QFile file (fileLocation);
    QStringList vUsers;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return vUsers;

    QByteArray parameterName;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        std::string strLine(line);

        auto parameter = line.split(':');
        auto parameterName = parameter[0];
        vUsers.push_back(parameterName);
    }

    return vUsers;
}

QString EditFtpConfigFile::OpenUserPathFile(const QString &fileLocation)
{
    QFile file (fileLocation);
    QString vUserPath;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return vUserPath;

    QByteArray parameterName;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        auto line2 = line.split('=');
        auto path = line2[1];
        vUserPath.push_back(path);
    }

    return vUserPath;
}

void EditFtpConfigFile::DeleteUsersFile(const QString user)
{
    QString commend = "rm /etc/vsftpd_user_conf/";
    commend.push_back(user);
    QProcess::execute(commend);
}

void EditFtpConfigFile::AddUser(const QString userName, const QString password)
{
    QString commend = "htpasswd -b -d /etc/vsftpd/ftpd.passwd ";
    commend.push_back(userName);
    commend.push_back(" ");
    commend.push_back(password);
    //qDebug() << commend;
    QProcess::execute(commend);
}

void EditFtpConfigFile::DeleteUser(const QString userName)
{
    QString commend = "htpasswd -D /etc/vsftpd/ftpd.passwd ";
    commend.push_back(userName);
    QProcess::execute(commend);
}

void EditFtpConfigFile::CreateUserConfigFile(const QString userName, const QString pathToFile)
{
        QString filename="/etc/vsftpd_user_conf/";
        filename.push_back(userName);
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << "local_root=" << pathToFile;
        }
        file.close();
}

