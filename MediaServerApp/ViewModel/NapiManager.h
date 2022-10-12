#ifndef NAPIMANAGER_H
#define NAPIMANAGER_H

#include "ConfigFile/DlnaConfigFile.h"
#include <QObject>
#include <vector>
#include <memory>


struct NapiConfig
{
    QString language;
};

class NapiManager : public QObject
{
    Q_OBJECT
public:
    explicit NapiManager(QObject *parent = nullptr);
    Q_INVOKABLE void init(QObject *englishLanguageRadioButton, QObject *polishLanguageRadioButton);
    Q_INVOKABLE void bNapiFileDialog_onAccepted(const QString folderPathFileDialot, const QString fileNameFileDialog);
    Q_INVOKABLE void bDownload_onClicked(QObject *text);
    Q_INVOKABLE void rbPolish_onClicked();
    Q_INVOKABLE void rbEnglish_onClicked();
    Q_INVOKABLE void setVideoPath(QObject *object);

private:
    const QString NAPI_CONFIG_FILE = "/etc/mediaserver/qnapi.ini";
    QString filePath;
    QString folderPath;
    QString fileName;
    DlnaConfigFile editDlnaConfigFile;
    NapiConfig napiConfig;
};

#endif// NAPIMANAGER_H
