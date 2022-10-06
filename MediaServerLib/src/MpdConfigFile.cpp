#include "MpdConfigFile.h"
#include <QFile>
#include <QDebug>
#include <iostream>

bool MpdConfigFile::read(QString& data)
{
    QFile file (fileName);

    std::map<QString, QString> mConfigsParameters;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    data = in.readAll();
    if (data.size()>0)
        return true;
    else
        return false;
}

bool MpdConfigFile::save(const QString data)
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

    qDebug() << fileString;

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
