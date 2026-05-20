#include "AlarmConfigFile.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
#include <QSettings>

AlarmConfigFile::AlarmConfigFile(const QString &configFilePath) : filePath(configFilePath)
{
}

bool AlarmConfigFile::LoadConfiguration(VectorData &configuration)
{
    QSettings settings(filePath, QSettings::IniFormat);

    if(settings.status() != QSettings::NoError)
        return false;

    settings.beginGroup("alarm");
    const QStringList keys = settings.allKeys();

    for(const QString &key : keys)
    {
        QString value = settings.value(key).toString();
        configuration.push_back(ConfigData(key, value));
    }
    settings.endGroup();

    return settings.status() == QSettings::NoError;
}

bool AlarmConfigFile::SaveConfiguration(const VectorData &mConfigsParameters)
{
    QSettings settings(filePath, QSettings::IniFormat);

    if(settings.status() != QSettings::NoError)
        return false;

    settings.beginGroup("alarm");

    for(const auto &configParam : mConfigsParameters)
    {
        settings.setValue(configParam.key, configParam.value);
    }

    settings.endGroup();
    settings.sync();

    return settings.status() == QSettings::NoError;
}
