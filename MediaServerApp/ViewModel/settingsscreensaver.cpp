#include "settings.h"
#include "mainwindow.h"

void Settings::bScreenSaverFileDialog_onAccepted(QString folderPath, QObject *tfScreenSavrFolderPath)
{
    QString path = folderPath.remove(0,7);
    tfScreenSavrFolderPath->setProperty("text",QVariant(path));
}

void Settings::bSaveScreenSaver_onClicked(const QString folderpath, const QString timeout)
{
    QString commend="DISPLAY=:0 feh -F -D" + timeout + " -x -S filename " + folderpath + " &\n" ;
    SaveScreenSaveConfiguration(commend,"/opt/startScreensaver.sh");

}

void Settings::SaveScreenSaveConfiguration(const QString &commend, const QString &fileLocation)
{
    QFile fileToRead(fileLocation);
    QStringList fileString;
    if (fileToRead.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fileToRead);

        while (!fileToRead.atEnd())
        {
            QByteArray line = fileToRead.readLine();
            std::string strLine(line);

            if(!line.contains("DISPLAY"))
            {
                fileString.push_back(line);
            }
            else
            {
                fileString.push_back(commend);
            }
        }
    }


    fileToRead.close();

    QFile fileToWrite(fileLocation);

    if (fileToWrite.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&fileToWrite);

        for(auto it :fileString)
        {
            stream << it;
        }
    }

    fileToWrite.close();

}
