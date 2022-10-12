#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/ConfigFile/MpdConfigFile.h"
#include "Mock/MockFileManager.h"

class openMpdConfigFileTest : public ::testing::Test {
};

TEST_F(openMpdConfigFileTest, readNotCall)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    MpdConfigFile editMpdConfigFile(mockReadFile);

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(0);
}

TEST_F(openMpdConfigFileTest, readFileOneLine)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData = "playlistdir \"/home/playlistdir\"";

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke([&](QString& fileData)
                      {
                          fileData = checkData;
                          return true;
                      }
              ));

    MpdConfigFile editMpdConfigFile(mockReadFile);

    VectorData fileData;

    auto result = editMpdConfigFile.OpenFile(fileData);
    EXPECT_TRUE(result);
    EXPECT_EQ(fileData.size(), std::size_t(1));

    EXPECT_EQ(fileData[0].key.toStdString(), "playlistdir");
    EXPECT_EQ(fileData[0].value.toStdString(), "/home/playlistdir");
}

TEST_F(openMpdConfigFileTest, readIncorrectFile)
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

    MpdConfigFile editMpdConfigFile(mockReadFile);

    VectorData fileData;

    auto result = editMpdConfigFile.OpenFile(fileData);

    EXPECT_FALSE(result);
}

TEST_F(openMpdConfigFileTest, readWholeFileData)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData =
           "music_directory \"/home/Music\"\n"
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

    MpdConfigFile editMpdConfigFile(mockReadFile);

    VectorData fileData;

    auto result = editMpdConfigFile.OpenFile(fileData);

    EXPECT_TRUE(result);

    EXPECT_EQ(fileData.size(), std::size_t(3));

    auto it = fileData.begin();
    EXPECT_EQ(it->key.toStdString(), "music_directory");
    EXPECT_EQ(it->value.toStdString(), "/home/Music");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "playlist_directory");
    EXPECT_EQ(it->value.toStdString(), "/home/Music/playlists");


    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "auto_update");
    EXPECT_EQ(it->value.toStdString(), "yes");

}

TEST_F(openMpdConfigFileTest, saveWholeFileData)
{
    EXPECT_TRUE(false);
}

