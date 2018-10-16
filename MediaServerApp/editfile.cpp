#include "editfile.h"
#include <QFile>
#include <QDebug>
#include <string>
#include <vector>
#include <map>
#include <utility>

EditFile::EditFile()
{

}

void EditFile::OpenFile()
{

    std::vector<std::string> vConfigName;
    std::vector<std::map<std::string,std::string>> vConfigParameters;
    std::map<std::string,std::string> mConfigParameters;

    QFile file ("/etc/samba/smb.conf");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        qDebug() << line;
        std::string str(line);
        if(!str.find('['))
        {
            vConfigName.push_back(str);
            //mConfigParameters.clear();
        }
        else
        {

            //auto test = str.split('=');

            //auto ds = std::to_string(test[0]);
            //mConfigParameters[test[0]]=test[1];
            //mConfigParameters.insert(std::make_pair(test[0],test[1]));
        }

        //auto test = line.split('=');


    }
}
