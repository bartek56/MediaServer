#include "napimanager.h"
#include <QtQuick>
#include <QProcess>
#include <QDir>
#include <QChar>
#include <QString>
#include <QFile>

NapiManager::NapiManager(QObject *parent) : QObject(parent)
{

}

void NapiManager::init(QObject *englishLanguageRadioButton, QObject *polishLanguageRadioButton)
{
   napiConfigFile = std::make_unique<EditHeadersConfigFile>(NAPI_CONFIG_FILE);
   napiConfig = napiConfigFile->OpenFile();
   QString language = napiConfig[0].configs.at("language");

   if(language=="en")
   {
       englishLanguageRadioButton->setProperty("checked",QVariant(true));
       polishLanguageRadioButton->setProperty("checked",QVariant(false));

   }
   else if (language=="pl")
   {
       englishLanguageRadioButton->setProperty("checked",QVariant(false));
       polishLanguageRadioButton->setProperty("checked",QVariant(true));
   }
}

void NapiManager::setVideoPath(QObject *object)
{
    auto dlnaConfig = editDlnaConfigFile.OpenFile();
    QString videoPath = "file://";
    videoPath += dlnaConfig.at("media_dir=V");
    object->setProperty("videoPath", QVariant(videoPath));
}

void NapiManager::bNapiFileDialog_onAccepted(const QString folderPathFileDialog, const QString fileNameFileDialog)
{
    QString temp = folderPathFileDialog;
    folderPath = temp.remove(0,7);
    fileName = fileNameFileDialog;
    filePath = folderPath+"/"+fileName;
}

void NapiManager::rbEnglish_onClicked()
{
    napiConfig[0].configs.at("language")="en";
}

void NapiManager::rbPolish_onClicked()
{
    napiConfig[0].configs.at("language")="pl";
}

void NapiManager::bDownload_onClicked(QObject * text)
{
    napiConfigFile->SaveFile(napiConfig);

    QProcess process;
    QString commend = "cd /etc/mediaserver && qnapi -q \"" + filePath + "\"";
    QStringList commend_new;
    commend_new << "-c" << commend;
    process.start("bash", commend_new);
    while(process.waitForFinished());
    process.close();

    QStringList fileList = fileName.split('.');
    auto movieExtended = fileList.last();

    QString fileNameCopy = fileName;
    QString movieName = fileNameCopy.replace("."+movieExtended,"");
    QString subtitlesFileName = movieName;
    subtitlesFileName.append(".srt");

    if(QFile::exists(folderPath + "/" + subtitlesFileName))
    {
        text->setProperty("text",QVariant("Succesfull downloaded subtitles"));
        QFile file(folderPath+"/"+subtitlesFileName);
        bool result = file.rename(folderPath+"/"+movieName+"."+napiConfig[0].configs.at("language")+".srt");
        if(!result)
        {
            QFile oldFile(folderPath+"/"+movieName+"."+napiConfig[0].configs.at("language")+".srt");
            oldFile.remove();
            file.rename(folderPath+"/"+movieName+"."+napiConfig[0].configs.at("language")+".srt");
        }

        file.close();
    }
    else
        text->setProperty("text",QVariant("Failed download subtitles"));

}
