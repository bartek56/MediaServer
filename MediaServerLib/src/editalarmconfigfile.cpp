#include "editalarmconfigfile.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

std::map<QString,QString> EditAlarmConfigFile::LoadConfiguration()
{
    std::map<QString,QString> mConfigsParameters;
    QFile fileToRead(ALARM_SCRIPT);
    QStringList fileString;
    if (fileToRead.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fileToRead);
        int lineNumber=1;

        fileToRead.readLine();

        while (lineNumber<8)
        {
            QByteArray line = fileToRead.readLine();

            auto parameter = line.split('=');
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            QString parameterValueString = QTextCodec::codecForMib(106)->toUnicode(parameterValue); // to UTF-8
            QString parameterNameString = QTextCodec::codecForMib(106)->toUnicode(parameterName); // to UTF-8
            parameterValueString.remove('"');
            parameterValueString.remove(parameterValueString.length()-1,1); // remove '\n' on last sign
            mConfigsParameters.insert(std::make_pair(parameterNameString,parameterValueString));
            lineNumber++;
        }
    }

    fileToRead.close();
    return mConfigsParameters;
}

void EditAlarmConfigFile::SaveConfiguration(const std::map<QString,QString> &mConfigsParameters)
{
    QFile fileToRead(ALARM_SCRIPT);
    QStringList fileString;
    if (fileToRead.open(QIODevice::ReadOnly))
    {
        int lineNumber=0;

        while (!fileToRead.atEnd())
        {
            QByteArray line = fileToRead.readLine();

            if(lineNumber>0 && lineNumber<8)
            {
                QString newLine;
                auto parametr = line.split('=');
                auto parametrName = parametr[0];
                if(parametrName.contains("playlist"))
                {
                    newLine= parametrName + "=\"" + mConfigsParameters.at(parametrName)+"\"\n";
                }
                else
                {
                    newLine = parametrName + "=" + mConfigsParameters.at(parametrName)+"\n";
                }

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

    QFile fileToWrite(ALARM_SCRIPT);

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
