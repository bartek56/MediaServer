#include "DlnaConfigFile.h"

#include <QFile>
#include <QDebug>

DlnaConfigFile::DlnaConfigFile(std::unique_ptr<IFileManager> ptrFileManager) : fileManager(std::move(ptrFileManager))
{}



bool DlnaConfigFile::LoadConfiguration(VectorData& configuration)
{
    QString fileData="";
    const bool res = fileManager->read(fileData);
    if (!res)
    {
        qDebug() << "Error to read File";
        return false;
    }

    QStringList lines = fileData.split('\n');

    for (int i = 0; i<lines.size(); i++)
    {
        QString line = lines[i];
        if (line <= 2)
            break;
        if(line.contains("media_dir"))
        {
            auto parameter = line.split(',');
            if(parameter.size()<2)
                return false;
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            configuration.push_back(ConfigData(parameterName,parameterValue));
        }
        else
        {
            auto parameter = line.split('=');
            if(parameter.size()<2)
                return false;
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            configuration.push_back(ConfigData(parameterName,parameterValue));
        }
    }
    return true;
}

bool DlnaConfigFile::SaveConfiguration(const VectorData &mConfigsParameters)
{
    QString dataToFile;
    for (const auto& configParam : mConfigsParameters)
    {
        QString lineData;
        if (configParam.key.contains("media_dir"))
            lineData = configParam.key + "," + configParam.value + "\n";
        else
            lineData = configParam.key + "=" + configParam.value + "\n";

        dataToFile.push_back(lineData);
    }

    bool result = fileManager->save(dataToFile);
    return result;
}
