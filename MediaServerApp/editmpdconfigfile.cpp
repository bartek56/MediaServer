#include "editmpdconfigfile.h"
#include <QFile>
#include <QDebug>


std::map<QString, QString> EditMpdConfigFile::OpenFile()
{
    QFile file (MPDCONFIG_PATH);

    std::map<QString, QString> mConfigsParameters;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return mConfigsParameters;

    QTextStream in(&file);
    QString line = in.readLine();
    while(line.size()>2)
    {
        auto parameter = line.split(' ');
        auto parameterName = parameter[0];
        auto parameterValue = parameter[1];
        parameterValue.remove(parameterValue.length()-1,1);
        parameterValue.remove(0,1);
        mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));

        line = in.readLine();
    }
    return mConfigsParameters;
}

void EditMpdConfigFile::SaveFile(const std::map<QString, QString> &mConfigs)
{
    QFile fileToRead(MPDCONFIG_PATH);
    QString fileString;

    if (fileToRead.open(QIODevice::ReadOnly))
    {

        int lineNumber=0;
        bool skipLastParameters=false;

        while (!fileToRead.atEnd())
        {
            QByteArray line = fileToRead.readLine();

            if(line.size()>2)
            {
                if(!skipLastParameters)
                {
                    QString newLine;
                    auto parametr = line.split(' ');
                    auto parametrName = parametr[0];
                    newLine= parametrName + " \"" + mConfigs.at(parametrName)+"\"\n";
                    fileString.push_back(newLine);
                }
            }
            else
            {
                skipLastParameters=true;
            }

            if(skipLastParameters)
            {
                fileString.push_back(line);
            }
            lineNumber++;
        }
    }
    fileToRead.close();


    QFile fileToWrite(MPDCONFIG_PATH);
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
