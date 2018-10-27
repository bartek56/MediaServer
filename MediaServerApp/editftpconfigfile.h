#ifndef EDITFTPCONFIGFILE_H
#define EDITFTPCONFIGFILE_H

#include <QString>
#include <vector>

class EditFtpConfigFile
{
public:
    EditFtpConfigFile();
    QStringList OpenFile(QString fileLocation);
};

#endif // EDITFTPCONFIGFILE_H
