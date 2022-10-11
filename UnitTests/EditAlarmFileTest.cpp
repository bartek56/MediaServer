#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/src/EditAlarmConfigFile.h"
#include "../MediaServerLib/src/VectorData.h"
#include "Mock/MockFileManager.h"
#include <stdio.h>


class openAlarmConfigFileTest : public ::testing::Test {
};
TEST_F(openAlarmConfigFileTest, readNotCall)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    EditAlarmConfigFile editAlarmConfigFile(mockReadFile);

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(0);
}

TEST_F(openAlarmConfigFileTest, readFileOneLine)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData = "playlist=\"Alarm\"";

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke([&](QString& fileData)
                      {
                          fileData = checkData;
                          return true;
                      }
              ));

    EditAlarmConfigFile editAlarmConfigFile(mockReadFile);

    VectorData fileData;

    auto result = editAlarmConfigFile.LoadConfiguration(fileData);
    EXPECT_TRUE(result);
    EXPECT_EQ(fileData.size(), std::size_t(1));

    EXPECT_EQ(fileData[0].key.toStdString(), "playlist");
    EXPECT_EQ(fileData[0].value.toStdString(), "Alarm");
}

TEST_F(openAlarmConfigFileTest, readIncorrectFile)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData =
           "music_directory\"/home/Music\"\n"
           "playlist_directory \"/home/Music/playlists\"\n"
            "auto_update \"yes\"\n"
            "\n"
            "\n"
            "audio_output { \n"
            "    type \"pulse\" \n"
            "    name \"Local Pulse\" \n"
            "} \n";

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke([&](QString& fileData)
                      {
                          fileData = checkData;
                          return true;
                      }
              ));

    EditAlarmConfigFile editAlarmConfigFile(mockReadFile);

    VectorData fileData;

    auto result = editAlarmConfigFile.LoadConfiguration(fileData);

    EXPECT_FALSE(result);
}

TEST_F(openAlarmConfigFileTest, readWholeFileData)
{

    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData =
           "minVolume=5\n"
           "maxVolume=50\n"
           "playlist=\"alarm\"\n"
            "theNewestSong=true\n"
            "\n"
            "\n"
            "set -e\n"
            "IFS=$\'\\n\' \n"
            "musicDirectoryTemp=$( cat /etc/mpd.conf | grep music_directory | awk \'{$1=\"\"}1\' )\n"
            "musicDirectoryTemp=${musicDirectoryTemp:1}\n"
            "musicDirectory=\"${musicDirectoryTemp//\"}\"\n";

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke([&](QString& fileData)
                      {
                          fileData = checkData;
                          return true;
                      }
              ));

    EditAlarmConfigFile editAlarmConfigFile(mockReadFile);

    VectorData fileData;


    auto result = editAlarmConfigFile.LoadConfiguration(fileData);

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

TEST_F(openAlarmConfigFileTest, saveWholeFileData)
{

    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString savingData;

    EXPECT_CALL(*mockReadFile, save(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke([&](const QString& fileData)
                      {
                          savingData = fileData;
                          return true;
                      }
              ));



    EditAlarmConfigFile editAlarmConfigFile(mockReadFile);

    VectorData fileData;

    fileData.push_back(ConfigData("minVolume","5"));
    fileData.push_back(ConfigData("maxVolume","50"));
    fileData.push_back(ConfigData("playlist","alarm"));
    fileData.push_back(ConfigData("theNewestSong","true"));

    auto result = editAlarmConfigFile.SaveConfiguration(fileData);

    EXPECT_TRUE(result);

    QStringList list = savingData.split("\n");
    list.pop_back(); // remove last empty QString - reason of split

    EXPECT_EQ(list.size(), 4);

    EXPECT_EQ(list[0].toStdString(), "minVolume=5");
    EXPECT_EQ(list[1].toStdString(), "maxVolume=50");
    EXPECT_EQ(list[2].toStdString(), "playlist=\"alarm\"");
    EXPECT_EQ(list[3].toStdString(), "theNewestSong=true");
}

