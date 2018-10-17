#include "editfile.h"
#include <QFile>
#include <QDebug>

#include <utility>
/*
EditFile::EditFile()
{

}
*/
std::map<QString,std::map<QByteArray,QByteArray>> EditFile::OpenFile(QString fileLocation)
{

    QFile file (fileLocation);
    std::map<QString,std::map<QByteArray,QByteArray>> configParametersMap;
    std::map<QByteArray,QByteArray> mConfigParameters;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return configParametersMap;

    QByteArray parameterName;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        std::string strLine(line);

        if(!strLine.find('['))
        {
            if(!mConfigParameters.empty())
            {
                configParametersMap.insert(std::make_pair(parameterName,mConfigParameters));
                mConfigParameters.clear();
            }
            parameterName=line.remove(line.length()-1,1);
        }
        else
        {
            auto test = line.split('=');
            test[1].remove(test[1].length()-1,1); // remove '\n' on last sign
            mConfigParameters.insert(std::make_pair(test[0],test[1]));
        }
    }
    configParametersMap.insert(std::make_pair(parameterName,mConfigParameters));
    mConfigParameters.clear();

    return configParametersMap;

}

