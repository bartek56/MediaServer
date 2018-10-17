#ifndef EDITFILE_H
#define EDITFILE_H

#include <QString>
#include <vector>
#include <map>

class EditFile
{
public:
    //EditFile();
    std::map<QString,std::map<QByteArray,QByteArray>> OpenFile(QString fileLocation);
    void ReadFile();

private:
};


#endif // EDITFILE_H
