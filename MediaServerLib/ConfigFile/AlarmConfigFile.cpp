#include "AlarmConfigFile.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>

AlarmConfigFile::AlarmConfigFile(std::unique_ptr<IFileManager> ptrFileManager) : fileManager(std::move(ptrFileManager))
{
}

bool AlarmConfigFile::LoadConfiguration(VectorData &configuration)
{
    QString fileData = "";
    const bool result = fileManager->read(fileData);

    if(!result)
        return false;

    QStringList lines = fileData.split('\n');

    for(int i = 0; i < lines.size(); i++)
    {
        if(lines[i] <= 2)
            break;
        auto parameter = lines[i].split("=");
        if(parameter.size() != 2)
            return false;
        auto parameterName = parameter[0];
        auto parameterValue = parameter[1];

        parameterValue.remove('"');
        configuration.push_back(ConfigData(parameterName, parameterValue));
    }
    return true;
}

bool AlarmConfigFile::SaveConfiguration(const VectorData &mConfigsParameters)
{
    QString dataToFile;
    for(const auto &configParam : mConfigsParameters)
    {
        QString lineData;
        if(configParam.key == "playlist")
            lineData = configParam.key + "=\"" + configParam.value + "\"\n";
        else
            lineData = configParam.key + "=" + configParam.value + "\n";

        dataToFile.push_back(lineData);
    }

    bool result = fileManager->save(dataToFile);
    return result;
}
