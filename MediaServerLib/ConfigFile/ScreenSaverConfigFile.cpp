#include "ScreenSaverConfigFile.h"
#include "IConfigFile.h"
#include <QFile>
#include <QTextStream>

ScreenSaverConfigFile::ScreenSaverConfigFile(std::unique_ptr<IFileManager> ptrFileManager) : fileManager(std::move(ptrFileManager))
{
}

bool ScreenSaverConfigFile::LoadConfiguration(VectorData &configs)
{
    QString fileData = "";
    bool ret = fileManager->read(fileData);
    if(!ret)
        return false;

    QStringList lines = fileData.split('\n');
    for(int i = 0; i < lines.size(); i++)
    {
        auto line = lines[i];
        if(line < 2)
            break;
        auto parameter = line.split('=');
        if(parameter.size() != 2)
            return false;

        auto parameterName = parameter[0];
        auto parameterValue = parameter[1];
        parameterValue.remove(parameterValue.length() - 1, 1);
        parameterValue.remove(0, 1);
        configs.push_back(ConfigData(parameterName, parameterValue));
    }
    return true;
}

bool ScreenSaverConfigFile::SaveConfiguration(const VectorData &configs)
{
    QString dataToFile;
    for(const auto &[key, value] : configs)
    {
        QString lineData;
        lineData = key + "=\"" + value + "\"\n";
        dataToFile.push_back(lineData);
    }

    bool result = fileManager->save(dataToFile);
    return result;
}
