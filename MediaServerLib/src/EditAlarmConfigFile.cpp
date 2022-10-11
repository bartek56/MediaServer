#include "EditAlarmConfigFile.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>

EditAlarmConfigFile::EditAlarmConfigFile(std::shared_ptr<IFileManager> ptrFileManager) : fileManager(std::move(ptrFileManager))
{
}

bool EditAlarmConfigFile::LoadConfiguration(VectorData& configuration)
{
    QString fileData="";
    fileManager->read(fileData);

    QStringList lines = fileData.split('\n');

    for (int i = 0; i<lines.size(); i++)
    {
        if (lines[i] <= 2)
            break;
        auto parameter = lines[i].split("=");
        if (parameter.size() != 2)
            return false;
        auto parameterName = parameter[0];
        auto parameterValue = parameter[1];

        parameterValue.remove('"');
        configuration.push_back(ConfigData(parameterName,parameterValue));
    }
    return true;
}

bool EditAlarmConfigFile::SaveConfiguration(const VectorData &mConfigsParameters)
{
    QString dataToFile;
    for (const auto& configParam : mConfigsParameters)
    {
        QString lineData;
        if (configParam.key == "playlist")
            lineData = configParam.key + "=\"" + configParam.value + "\"\n";
        else
            lineData = configParam.key + "=" + configParam.value + "\n";

        dataToFile.push_back(lineData);
    }

    bool result = fileManager->save(dataToFile);
    return result;
}
