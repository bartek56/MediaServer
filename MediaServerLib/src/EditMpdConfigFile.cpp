#include "EditMpdConfigFile.h"
#include <QFile>
#include <QDebug>
#include <iostream>

EditMpdConfigFile::EditMpdConfigFile(std::shared_ptr<IFileManager> ptrFileManager) : fileManager(std::move(ptrFileManager))
{
}

bool EditMpdConfigFile::OpenFile(VectorData& mConfigsParameters)
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

void EditMpdConfigFile::SaveFile(const VectorData &mConfigs)
{
    QString dataToFile;
    for (const auto& [key, value] : mConfigs)
    {
        QString lineData;
        lineData = key + " \"" + value + "\"\n";
        dataToFile.push_front(lineData);
    }

    bool result = fileManager->save(dataToFile);

    if(result)
        qDebug() << "succesfully saved MPD file";
}
