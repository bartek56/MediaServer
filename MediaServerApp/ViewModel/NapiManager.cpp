#include "NapiManager.h"
#include "ConfigFile/ConfigFile.h"
#include <QtQuick>
#include <QProcess>
#include <QDir>
#include <QChar>
#include <QString>
#include <QFile>

NapiManager::NapiManager(QObject *parent) : QObject(parent), dlnaConfigFile(std::make_unique<ConfigFile>(MINIDLNA_CONFIG_FILE))
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
    if(dlnaConfigFile.LoadConfiguration(dlnaConfig))
    {
        QString videoPath = "file://";
        videoPath += dlnaConfig.getValueByKey("media_dir=V");
        object->setProperty("videoPath", QVariant(videoPath));
    }
    else
    {
        qWarning("Failed to read dlna config");
    }
}

bool NapiManager::isQNapiSupport() const
{
    if(!QFile("/usr/bin/qnapi").exists())
    {
        qCritical("QNapi doesn't exist");
        return false;
    }

    if(!QFile(NAPI_CONFIG_FILE).exists())
    {
        qCritical("QNapi config file doesn't exist");
        return false;
    }

    return true;
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
    QString commend = "cd " + QString(CONFIG_PATH) + " && qnapi -q \"" + filePath + "\"";
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
