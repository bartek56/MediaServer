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
    QSettings settings(NAPI_CONFIG_FILE, QSettings::IniFormat);
    QString language = settings.value("qnapi/language", QVariant("pl")).toString();

    if(language == "en")
    {
        englishLanguageRadioButton->setProperty("checked", QVariant(true));
        polishLanguageRadioButton->setProperty("checked", QVariant(false));
    }
    else if(language == "pl")
    {
        englishLanguageRadioButton->setProperty("checked", QVariant(false));
        polishLanguageRadioButton->setProperty("checked", QVariant(true));
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
    folderPath = temp.remove(0, 7);
    fileName = fileNameFileDialog;
    filePath = folderPath + "/" + fileName;
}

void NapiManager::rbEnglish_onClicked()
{
    napiConfig.language = "en";
}

void NapiManager::rbPolish_onClicked()
{
    napiConfig.language = "pl";
}

void NapiManager::bDownload_onClicked(QObject *text)
{
    QSettings settings(NAPI_CONFIG_FILE, QSettings::IniFormat);

    settings.setValue("qnapi/language", QVariant(napiConfig.language));
    settings.sync();
    QProcess process;
    QString commend = "cd /etc/mediaserver && qnapi -q \"" + filePath + "\"";
    QStringList commend_new;
    commend_new << "-c" << commend;
    process.start("bash", commend_new);
    while(process.waitForFinished())
        ;
    process.close();

    QStringList fileList = fileName.split('.');
    auto movieExtended = fileList.last();

    QString fileNameCopy = fileName;
    QString movieName = fileNameCopy.replace("." + movieExtended, "");
    QString subtitlesFileName = movieName;
    subtitlesFileName.append(".srt");

    if(QFile::exists(folderPath + "/" + subtitlesFileName))
    {
        text->setProperty("text", QVariant("Succesfull downloaded subtitles"));
        QFile file(folderPath + "/" + subtitlesFileName);
        bool result = file.copy(folderPath + "/" + movieName + "." + napiConfig.language + ".srt");
        if(!result)
        {
            QFile oldFile(folderPath + "/" + movieName + "." + napiConfig.language + ".srt");
            oldFile.remove();
            file.copy(folderPath + "/" + movieName + "." + napiConfig.language + ".srt");
        }
        file.close();
    }
    else
        text->setProperty("text", QVariant("Failed download subtitles"));
}
