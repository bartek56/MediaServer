#include "DlnaConfigFile.h"
#include <QFile>
#include <QDebug>

std::map<QString, QString> DlnaConfigFile::OpenFile()
{

    QFile file(DLNA_CONFIG);

    std::map<QString, QString> mConfigsParameters;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return mConfigsParameters;

    QByteArray parameterName;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        std::string strLine(line);
        if(line.contains("media_dir"))
        {
            auto parameter = line.split(',');
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            parameterValue.remove(parameterValue.length()-1,1);
            mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
        }
        else
        {
            auto parameter = line.split('=');
            auto parameterName = parameter[0];
            auto parameterValue = parameter[1];
            parameterValue.remove(parameterValue.length()-1,1);
            mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
        }
    }
    return mConfigsParameters;
}

void DlnaConfigFile::SaveFile(const std::map<QString, QString> &mConfigs)
{
    QFile file(DLNA_CONFIG);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (auto it = std::begin(mConfigs); it!=std::end(mConfigs); ++it)
    {
        if(it->first.contains("media_dir"))
        {
            out << it->first << "," << it->second << "\n";
        }
        else
        {
            out << it->first << "=" << it->second << "\n";
        }

    }
    file.close();
}
