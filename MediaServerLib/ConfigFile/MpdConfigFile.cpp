#include "MpdConfigFile.h"
#include <QFile>
#include <QDebug>
#include <iostream>

MpdConfigFile::MpdConfigFile(std::shared_ptr<IFileManager> ptrFileManager) : fileManager(std::move(ptrFileManager))
{
}

bool MpdConfigFile::OpenFile(VectorData& mConfigsParameters)
{
    QString fileData="";
    fileManager->read(fileData);

    QStringList lines = fileData.split('\n');

    for (int i = 0; i<lines.size(); i++)
    {
        if (lines[i] <= 1)
            break;
        auto parameter = lines[i].split(" \"");
        if (parameter.size() != 2)
            return false;
        auto parameterName = parameter[0];
        auto parameterValue = parameter[1];
        parameterValue.remove(parameterValue.length()-1,1);
        mConfigsParameters.push_back(ConfigData(parameterName,parameterValue));
    }
    return true;
}

bool MpdConfigFile::SaveFile(const VectorData &mConfigs)
{
    QString dataToFile;
    for (const auto& [key, value] : mConfigs)
    {
        QString lineData;
        lineData = key + " \"" + value + "\"\n";
        dataToFile.push_back(lineData);
    }

    bool result = fileManager->save(dataToFile);
    return result;
}
