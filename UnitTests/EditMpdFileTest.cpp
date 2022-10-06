#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/src/EditMpdConfigFile.h"
#include "Mock/MockFileManager.h"

class openMpdConfigFileTest : public ::testing::Test {
};

TEST_F(openMpdConfigFileTest, readNotCall)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    EditMpdConfigFile editMpdConfigFile(mockReadFile);

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

    EditMpdConfigFile editMpdConfigFile(mockReadFile);

    std::unordered_map<QString, QString> fileData;

    auto result = editMpdConfigFile.OpenFile(fileData);
    EXPECT_TRUE(result);
    EXPECT_EQ(fileData.size(), std::size_t(1));

    EXPECT_EQ(fileData.cbegin()->first.toStdString(), "playlistdir");
    EXPECT_EQ(fileData.cbegin()->second.toStdString(), "/home/playlistdir");
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

    EditMpdConfigFile editMpdConfigFile(mockReadFile);

    std::unordered_map<QString, QString> fileData;

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

    EditMpdConfigFile editMpdConfigFile(mockReadFile);

    std::unordered_map<QString, QString> fileData;

    auto result = editMpdConfigFile.OpenFile(fileData);

    EXPECT_TRUE(result);

    EXPECT_EQ(fileData.size(), std::size_t(3));

    auto it = fileData.end();

    EXPECT_EQ(it->first.toStdString(), "music_directory");
    EXPECT_EQ(it->second.toStdString(), "/home/Music");

    it = std::prev(it);
    EXPECT_EQ(it->first.toStdString(), "playlist_directory");
    EXPECT_EQ(it->second.toStdString(), "/home/Music/playlists");

    it = std::prev(it);
    EXPECT_EQ(it->first.toStdString(), "auto_update");
    EXPECT_EQ(it->second.toStdString(), "yes");
}
