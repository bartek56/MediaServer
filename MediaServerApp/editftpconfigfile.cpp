#include "editftpconfigfile.h"

#include <QFile>

EditFtpConfigFile::EditFtpConfigFile()
{

}

QStringList EditFtpConfigFile::OpenFile(QString fileLocation)
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
