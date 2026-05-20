#include <gtest/gtest.h>
#include <QDebug>
#include <QTemporaryFile>
#include <QTextStream>
#include <QSettings>
#include "../MediaServerLib/ConfigFile/AlarmConfigFile.h"
#include "../MediaServerLib/Utils/VectorData.h"


class AlarmConfigFileTest : public ::testing::Test
{
    virtual void SetUp()
    {
        tempFile = new QTemporaryFile();
        tempFile->setFileTemplate(tempFile->fileTemplate() + ".ini");
        tempFile->open();
        tempFilePath = tempFile->fileName();
        tempFile->close();
        alarmConfigFile = std::make_unique<AlarmConfigFile>(tempFilePath);
    }

    virtual void TearDown()
    {
        delete tempFile;
    }

protected:
    QTemporaryFile *tempFile;
    QString tempFilePath;
    std::unique_ptr<AlarmConfigFile> alarmConfigFile;
};

TEST_F(AlarmConfigFileTest, configFileNotExist)
{
    AlarmConfigFile config("/nonexistent/path/to/alarm.ini");
    VectorData fileData;

    EXPECT_FALSE(config.LoadConfiguration(fileData));
    EXPECT_TRUE(fileData.empty());
}

TEST_F(AlarmConfigFileTest, readFileOneLine)
{
    QSettings settings(tempFilePath, QSettings::IniFormat);
    settings.beginGroup("alarm");
    settings.setValue("playlist", "Alarm");
    settings.endGroup();
    settings.sync();

    VectorData fileData;

    auto result = alarmConfigFile->LoadConfiguration(fileData);
    EXPECT_TRUE(result);
    EXPECT_EQ(fileData.size(), std::size_t(1));

    EXPECT_EQ(fileData[0].key.toStdString(), "playlist");
    EXPECT_EQ(fileData[0].value.toStdString(), "Alarm");
}

TEST_F(AlarmConfigFileTest, readWholeFileData)
{
    QSettings settings(tempFilePath, QSettings::IniFormat);
    settings.beginGroup("alarm");
    settings.setValue("minVolume", "5");
    settings.setValue("maxVolume", "50");
    settings.setValue("playlist", "alarm");
    settings.setValue("theNewestSong", "true");
    settings.endGroup();
    settings.sync();

    VectorData fileData;

    auto result = alarmConfigFile->LoadConfiguration(fileData);

    EXPECT_TRUE(result);

    EXPECT_EQ(fileData.size(), std::size_t(4));

    EXPECT_EQ(fileData.getValueByKey(QString("minVolume")).toStdString(), "5");
    EXPECT_EQ(fileData.getValueByKey(QString("maxVolume")).toStdString(), "50");
    EXPECT_EQ(fileData.getValueByKey(QString("playlist")).toStdString(), "alarm");
    EXPECT_EQ(fileData.getValueByKey(QString("theNewestSong")).toStdString(), "true");

    EXPECT_TRUE(fileData.setValueByKey(QString("theNewestSong"), QString("false")));

    auto it = fileData.begin();
    EXPECT_EQ(it->key.toStdString(), "minVolume");
    EXPECT_EQ(it->value.toStdString(), "5");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "maxVolume");
    EXPECT_EQ(it->value.toStdString(), "50");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "playlist");
    EXPECT_EQ(it->value.toStdString(), "alarm");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "theNewestSong");
    EXPECT_EQ(it->value.toStdString(), "false");
}

TEST_F(AlarmConfigFileTest, saveWholeFileData)
{
    VectorData fileData;

    fileData.push_back(ConfigData("minVolume", "5"));
    fileData.push_back(ConfigData("maxVolume", "50"));
    fileData.push_back(ConfigData("playlist", "alarm"));
    fileData.push_back(ConfigData("theNewestSong", "true"));

    auto result = alarmConfigFile->SaveConfiguration(fileData);

    EXPECT_TRUE(result);

    // Verify by reading back the file
    QSettings settings(tempFilePath, QSettings::IniFormat);
    settings.beginGroup("alarm");

    EXPECT_EQ(settings.value("minVolume").toString().toStdString(), "5");
    EXPECT_EQ(settings.value("maxVolume").toString().toStdString(), "50");
    EXPECT_EQ(settings.value("playlist").toString().toStdString(), "alarm");
    EXPECT_EQ(settings.value("theNewestSong").toString().toStdString(), "true");

    settings.endGroup();
}
