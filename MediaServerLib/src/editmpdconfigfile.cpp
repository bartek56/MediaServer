#include "editmpdconfigfile.h"
#include <QFile>
#include <QDebug>
#include <iostream>

EditMpdConfigFile::EditMpdConfigFile(std::shared_ptr<IFileManager> ptrFileManager) : fileManager(std::move(ptrFileManager))
{
}

std::unordered_map<QString, QString> EditMpdConfigFile::OpenFile()
{
    QString fileData="";
    fileManager->read(fileData);

    std::unordered_map<QString, QString> mConfigsParameters;

    QStringList lines = fileData.split('\n');

    for (int i = 0; i<lines.size(); i++)
    {
        if (lines[i] <= 2)
            break;
        auto parameter = lines[i].split(" \"");
        auto parameterName = parameter[0];
        auto parameterValue = parameter[1];
        parameterValue.remove(parameterValue.length()-1,1);
        mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
    }
    return mConfigsParameters;
}

void EditMpdConfigFile::SaveFile(const std::unordered_map<QString, QString> &mConfigs)
{
    qDebug() << "before saved";

    QString dataToFile;
    for (const auto& [key, value] : mConfigs)
    {
        QString lineData;
        lineData = key + " \"" + value + "\"\n";
        dataToFile.push_front(lineData);
    }
    qDebug() << dataToFile;


    bool result = fileManager->save(dataToFile);

    if(result)
        qDebug() << "succesfully saved MPD file";
}
