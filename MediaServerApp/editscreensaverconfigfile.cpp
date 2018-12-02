#include "editscreensaverconfigfile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

EditScreenSaverConfigFile::EditScreenSaverConfigFile()
{

}

std::map<QString,QString> EditScreenSaverConfigFile::LoadConfiguration(const QString &fileLocation)
{
    std::map<QString,QString> mConfigsParameters;
    QFile fileToRead(fileLocation);
    QStringList fileString;
    if (fileToRead.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fileToRead);
        int lineNumber=1;

        fileToRead.readLine();

        while (lineNumber<4)
        {
            QByteArray line = fileToRead.readLine();
            std::string strLine(line);
            auto parameter = line.split('=');
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            parameterValue.remove(parameterValue.length()-2,2);
            parameterValue.remove(0,1);
            mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
            lineNumber++;
        }
    }

    fileToRead.close();
    return mConfigsParameters;
}

void EditScreenSaverConfigFile::SaveConfiguration(const QString &fileLocation, const std::map<QString,QString> &mConfigsParameters)
{

    QFile fileToRead(fileLocation);
    QStringList fileString;
    if (fileToRead.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fileToRead);

        int lineNumber=0;

        while (!fileToRead.atEnd())
        {
            QByteArray line = fileToRead.readLine();
            std::string strLine(line);

            if(lineNumber>0 && lineNumber<4)
            {
                auto parametr = line.split('=');
                auto parametrName = parametr[0];
                qDebug() << parametrName;
                QString newLine = parametrName + "='" + mConfigsParameters.at(parametrName)+"'\n";
                fileString.push_back(newLine);
            }
            else
            {
                fileString.push_back(line);
            }
            lineNumber++;
        }
    }

    fileToRead.close();

    QFile fileToWrite(fileLocation);

    if (fileToWrite.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fileToWrite);

        for(auto it :fileString)
        {
            stream << it;
        }
    }
    fileToWrite.close();
}
