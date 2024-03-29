#include <gtest/gtest.h>
#include <QStringList>
#include "../MediaServerLib/ConfigFile/MpdConfigFile.h"
#include "Mock/MockFileManager.h"

class MpdConfigFileTest : public ::testing::Test
{
    virtual void SetUp() {
        mockFileManager = new MockFileManager();
        fileManager = std::unique_ptr<MockFileManager>(mockFileManager);
        mpdConfigFile = std::make_unique<MpdConfigFile>(std::move(fileManager));
    }

protected:
    MockFileManager* mockFileManager;
    std::unique_ptr<IFileManager> fileManager;
    std::unique_ptr<MpdConfigFile> mpdConfigFile;
};

TEST_F(MpdConfigFileTest, readNotCall)
{
    EXPECT_CALL(*mockFileManager, read(testing::_)).Times(0);
}

TEST_F(MpdConfigFileTest, configFileNotExist)
{
    EXPECT_CALL(*mockFileManager, read(testing::_)).Times(1).WillOnce(testing::Invoke([&](QString &) { return false; }));

    VectorData fileData;

    EXPECT_FALSE(mpdConfigFile->LoadConfiguration(fileData));
    EXPECT_TRUE(fileData.empty());
}

TEST_F(MpdConfigFileTest, readFileOneLine)
{
    QString checkData = "playlistdir \"/home/playlistdir\"";

    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    VectorData fileData;

    auto result = mpdConfigFile->LoadConfiguration(fileData);
    EXPECT_TRUE(result);
    EXPECT_EQ(fileData.size(), std::size_t(1));

    EXPECT_EQ(fileData[0].key.toStdString(), "playlistdir");
    EXPECT_EQ(fileData[0].value.toStdString(), "/home/playlistdir");
}

TEST_F(MpdConfigFileTest, readIncorrectFile)
{
    QString checkData = "music_directory\"/home/Music\"\n"
                        "playlist_directory \"/home/Music/playlists\"\n"
                        "auto_update \"yes\"\n"
                        "\n"
                        "\n"
                        "audio_output { \n"
                        "    type \"pulse\" \n"
                        "    name \"Local Pulse\" \n"
                        "} \n";

    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    VectorData fileData;

    auto result = mpdConfigFile->LoadConfiguration(fileData);

    EXPECT_FALSE(result);
}

TEST_F(MpdConfigFileTest, readWholeFileData)
{
    QString checkData = "music_directory \"/home/Music\"\n"
                        "playlist_directory \"/home/Music/playlists\"\n"
                        "auto_update \"yes\"\n"
                        "\n"
                        "\n"
                        "audio_output { \n"
                        "    type \"pulse\" \n"
                        "    name \"Local Pulse\" \n"
                        "} \n";

    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    VectorData fileData;

    auto result = mpdConfigFile->LoadConfiguration(fileData);

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

TEST_F(MpdConfigFileTest, saveWholeFileData)
{
    QString savingData;

    EXPECT_CALL(*mockFileManager, save(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](const QString &fileData)
                    {
                        savingData = fileData;
                        return true;
                    }));

    VectorData fileData;
    fileData.push_back(ConfigData("music_directory", "/mnt/TOSHIBA EXT/muzyka"));
    fileData.push_back(ConfigData("playlist_directory", "/mnt/TOSHIBA EXT/muzyka"));
    fileData.push_back(ConfigData("db_file", "/var/lib/mpd/mpd.db"));
    fileData.push_back(ConfigData("log_file", "/var/log/mpd.log"));
    fileData.push_back(ConfigData("pid_file", "/var/run/mpd.pid"));
    fileData.push_back(ConfigData("state_file", "/var/lib/mpd/state"));
    fileData.push_back(ConfigData("auto_update", "yes"));
    fileData.push_back(ConfigData("mixer_type", "software"));

    auto result = mpdConfigFile->SaveConfiguration(fileData);

    EXPECT_TRUE(result);

    QStringList list = savingData.split("\n");
    list.pop_back();// remove last empty QString - reason of split

    EXPECT_EQ(list.size(), 8);

    EXPECT_EQ(list[0].toStdString(), "music_directory \"/mnt/TOSHIBA EXT/muzyka\"");
    EXPECT_EQ(list[1].toStdString(), "playlist_directory \"/mnt/TOSHIBA EXT/muzyka\"");
    EXPECT_EQ(list[2].toStdString(), "db_file \"/var/lib/mpd/mpd.db\"");
    EXPECT_EQ(list[3].toStdString(), "log_file \"/var/log/mpd.log\"");
    EXPECT_EQ(list[4].toStdString(), "pid_file \"/var/run/mpd.pid\"");
    EXPECT_EQ(list[5].toStdString(), "state_file \"/var/lib/mpd/state\"");
    EXPECT_EQ(list[6].toStdString(), "auto_update \"yes\"");
    EXPECT_EQ(list[7].toStdString(), "mixer_type \"software\"");
}

class MpdConfigFileTestParam : public ::testing::TestWithParam<std::string>
{
};

TEST_P(MpdConfigFileTestParam, readFileFailed)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    auto param = GetParam();
    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = QString::fromStdString(param);
                        return true;
                    }));

    MpdConfigFile mpdConfigFile(std::move(fileManager));

    VectorData fileData;

    auto result = mpdConfigFile.LoadConfiguration(fileData);

    EXPECT_FALSE(result);
}

INSTANTIATE_TEST_SUITE_P(readFileFailed, MpdConfigFileTestParam,
                         ::testing::Values("auto_update\"yes\"",

                                           "auto_update \"yes\"\n\
music_directory=\"/home/music\"",

                                           "gfgfgf"));
