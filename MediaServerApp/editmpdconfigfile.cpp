#include "editmpdconfigfile.h"
#include <QFile>
#include <QDebug>


std::map<QString, QString> EditMpdConfigFile::OpenFile(QString fileLocation)
{

    QFile file (fileLocation);

    std::map<QString, QString> mConfigsParameters;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return mConfigsParameters;

    QByteArray parameterName;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        std::string strLine(line);
        auto parameter = line.split(' ');
        auto parameterName = parameter[0];
        auto parameterValue = parameter[1];
        parameterValue.remove(parameterValue.length()-2,2);
        parameterValue.remove(0,1);
        mConfigsParameters.insert(std::make_pair(parameterName,parameterValue));
    }
    return mConfigsParameters;
}

void EditMpdConfigFile::SaveFile(const std::map<QString, QString> &mConfigs)
{
    QString filename="/etc/mpd.conf";

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (auto it = std::begin(mConfigs); it!=std::end(mConfigs); ++it)
    {
        out << it->first << " " << "\"" << it->second << "\"\n";
    }
    file.close();
}
