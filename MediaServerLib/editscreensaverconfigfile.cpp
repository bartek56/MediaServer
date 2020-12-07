#include "editscreensaverconfigfile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

EditScreenSaverConfigFile::EditScreenSaverConfigFile()
{

}

std::map<QString,QString> EditScreenSaverConfigFile::LoadConfiguration()
{
    std::map<QString,QString> mConfigsParameters;
    QFile fileToRead(fileLocation);

    if (fileToRead.open(QIODevice::ReadOnly))
    {
        while (!fileToRead.atEnd())
        {
            QByteArray line = fileToRead.readLine();

            auto parameter = line.split('=');
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            parameterValue.remove(parameterValue.length()-2,2);
            parameterValue.remove(0,1);
            mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
        }
    }

    fileToRead.close();
    return mConfigsParameters;
}

void EditScreenSaverConfigFile::SaveConfiguration(const std::map<QString,QString> &mConfigsParameters)
{
    QFile file(fileLocation);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (auto it = std::begin(mConfigsParameters); it!=std::end(mConfigsParameters); ++it)
    {
        out << it->first << "='" << it->second << "'\n";

    }
    file.close();
}
