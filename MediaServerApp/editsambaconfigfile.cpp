#include "editsambaconfigfile.h"
#include <QFile>
#include <QDebug>
#include <vector>
#include <utility>
#include <QDebug>

std::vector<ConfigsName> EditSambaConfigFile::OpenFile(QString fileLocation)
{
    QFile file (fileLocation);
    std::vector<ConfigsName> vConfigsName;
    std::map<QString, QString> mConfigsParameters;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return vConfigsName;

    QByteArray parameterName;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        std::string strLine(line);

        if(!strLine.find('['))
        {
            if(!mConfigsParameters.empty())
            {
                vConfigsName.push_back(ConfigsName(parameterName,mConfigsParameters));
                mConfigsParameters.clear();
            }
            parameterName=line.remove(line.length()-1,1);
        }
        else
        {
            auto parameter = line.split('=');
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];

            parameterValue.remove(parameter[1].length()-1,1); // remove '\n' on last sign
            mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
        }
    }
    vConfigsName.push_back(ConfigsName(parameterName,mConfigsParameters));
    mConfigsParameters.clear();

    return vConfigsName;
}

void EditSambaConfigFile::SaveFile(QString fileLocation, std::vector<ConfigsName> vConfigs)
{
    QFile file(fileLocation);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (auto it = std::begin(vConfigs); it!=std::end(vConfigs); ++it)
    {
        out << it->name << "\n";
        auto configMap = it->configs;
        for (std::map<QString, QString>::iterator it2=configMap.begin(); it2!=configMap.end(); ++it2)
        {
            out << it2->first << "=" << it2->second << "\n";
        }
    }
}

