#include "editheadersconfigfile.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>


std::vector<HeadersConfig> EditHeadersConfigFile::OpenFile()
{
    QFile file (CONFIG_FILE);
    std::vector<HeadersConfig> vConfigsName;
    std::map<QString, QString> mConfigsParameters;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return vConfigsName;

    QByteArray parameterName;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        std::string strLine(line);
        QString qStrLine = QString(line);

        if(!strLine.find('['))
        {
            if(!mConfigsParameters.empty())
            {
                vConfigsName.push_back(HeadersConfig(parameterName,mConfigsParameters));
                mConfigsParameters.clear();
            }
            parameterName=line.remove(line.length()-1,1);
        }
        else
        {
            auto parameter = line.split('=');
            auto parameterName = qStrLine.section('=',0,0);
            auto parameterValue = qStrLine.section('=',1);

            qDebug() << parameterName << " " << parameterValue;
            parameterValue.remove(parameter[1].length()-1,1); // remove '\n' on last sign
            mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
        }
    }
    vConfigsName.push_back(HeadersConfig(parameterName,mConfigsParameters));
    mConfigsParameters.clear();

    return vConfigsName;
}

void EditHeadersConfigFile::SaveFile(std::vector<HeadersConfig> vConfigs)
{
    QFile file(CONFIG_FILE);
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


