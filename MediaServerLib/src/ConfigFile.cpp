#include "ConfigFile.h"
#include <QFile>
#include <QDebug>
#include <iostream>

ConfigFile::ConfigFile(const QString confFile): fileName(confFile)
{
}

bool ConfigFile::read(QString& data)
{
    QFile fileToRead(fileName);
    QString fileString;

    if (fileToRead.open(QIODevice::ReadOnly))
    {
        while (!fileToRead.atEnd())
        {
            QByteArray line = fileToRead.readLine();
            if (line[0] == '#')
            {
                continue;
            }
            fileString.push_back(line);
        }
    }
    else
    {
        fileToRead.close();
        return false;
    }

    fileToRead.close();
    data = fileString;
    return true;
}

bool ConfigFile::save(const QString data)
{
    QFile fileToRead(fileName);
    QString fileString;

    QStringList dataList = data.split("\n");
    int numberOfLines = data.count("\n");

    int lineNumber = 0;

    if (fileToRead.open(QIODevice::ReadOnly))
    {
        while (!fileToRead.atEnd())
        {
            QByteArray line = fileToRead.readLine();
            if (line[0] == '#')
            {
                fileString.push_back(line);
                continue;
            }

            if(lineNumber < numberOfLines)
            {
                QString newLine;
                newLine= dataList[lineNumber]+"\n";
                fileString.push_back(newLine);
                lineNumber++;
            }
            else
            {
                fileString.push_back(line);
            }
        }
    }
    else
        return false;

    fileToRead.close();

    QFile fileToWrite(fileName);
    if (fileToWrite.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fileToWrite);

        for(auto it :fileString)
        {
            stream << it;
        }
    }
    else
        return false;

    fileToWrite.close();
    return true;
}
