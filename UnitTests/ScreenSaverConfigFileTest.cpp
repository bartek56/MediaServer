#include "Mock/MockFileManager.h"
#include "../MediaServerLib/ConfigFile/ScreenSaverConfigFile.h"
#include <gtest/gtest.h>
#include <QStringList>

class ScreenSaverConfigFileTest : public ::testing::Test
{

protected:
    MockFileManager* mockFileManager;
};

TEST_F(ScreenSaverConfigFileTest, configFileNotExist)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);
    ScreenSaverConfigFile screenSaverConfigFile(std::move(fileManager));

    EXPECT_CALL(*mockFileManager, read(testing::_)).Times(1).WillOnce(testing::Invoke([&](QString &) { return false; }));

    VectorData fileData;

    EXPECT_FALSE(screenSaverConfigFile.LoadConfiguration(fileData));
    EXPECT_TRUE(fileData.empty());
}

TEST_F(ScreenSaverConfigFileTest, readNotCall)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);
    ScreenSaverConfigFile screenSaverConfigFile(std::move(fileManager));

    EXPECT_CALL(*mockFileManager, read(testing::_)).Times(0);
}


TEST_F(ScreenSaverConfigFileTest, readFileOneLine)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    QString checkData = "enable=\"false\"";

    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    ScreenSaverConfigFile screenSaverConfigFile(std::move(fileManager));

    VectorData fileData;

    auto result = screenSaverConfigFile.LoadConfiguration(fileData);
    EXPECT_TRUE(result);
    EXPECT_EQ(fileData.size(), std::size_t(1));

    EXPECT_EQ(fileData[0].key.toStdString(), "enable");
    EXPECT_EQ(fileData[0].value.toStdString(), "false");
}

TEST_F(ScreenSaverConfigFileTest, readWholeFile)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    QString checkData = "enable=\"false\"\n"
                        "path=\"/home/Pictures/tapety\"\n"
                        "random=\"true\"\n"
                        "startTime=\"60000\"\n"
                        "timeout=\"7\"\n"
                        "\n";

    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    ScreenSaverConfigFile screenSaverConfigFile(std::move(fileManager));

    VectorData fileData;

    auto result = screenSaverConfigFile.LoadConfiguration(fileData);

    EXPECT_TRUE(result);

    EXPECT_EQ(fileData.size(), std::size_t(5));

    auto it = fileData.begin();
    EXPECT_EQ(it->key.toStdString(), "enable");
    EXPECT_EQ(it->value.toStdString(), "false");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "path");
    EXPECT_EQ(it->value.toStdString(), "/home/Pictures/tapety");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "random");
    EXPECT_EQ(it->value.toStdString(), "true");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "startTime");
    EXPECT_EQ(it->value.toStdString(), "60000");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "timeout");
    EXPECT_EQ(it->value.toStdString(), "7");
}

TEST_F(ScreenSaverConfigFileTest, saveWholeFileData)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    QString savingData;

    EXPECT_CALL(*mockFileManager, save(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](const QString &fileData)
                    {
                        savingData = fileData;
                        return true;
                    }));

    ScreenSaverConfigFile screenSaverConfigFile(std::move(fileManager));

    VectorData fileData;
    fileData.push_back(ConfigData("enable", "false"));
    fileData.push_back(ConfigData("path", "/home/Pictures/tapety"));
    fileData.push_back(ConfigData("random", "true"));
    fileData.push_back(ConfigData("startTime", "60000"));
    fileData.push_back(ConfigData("timeout", "7"));

    auto result = screenSaverConfigFile.SaveConfiguration(fileData);

    EXPECT_TRUE(result);

    QStringList list = savingData.split("\n");
    list.pop_back();// remove last empty QString - reason of split

    EXPECT_EQ(list.size(), 5);

    EXPECT_EQ(list[0].toStdString(), "enable=\"false\"");
    EXPECT_EQ(list[1].toStdString(), "path=\"/home/Pictures/tapety\"");
    EXPECT_EQ(list[2].toStdString(), "random=\"true\"");
    EXPECT_EQ(list[3].toStdString(), "startTime=\"60000\"");
    EXPECT_EQ(list[4].toStdString(), "timeout=\"7\"");
}


class ScreenSaverConfigFileTestParam : public ::testing::TestWithParam<std::string>
{
};

TEST_P(ScreenSaverConfigFileTestParam, readFileFailed)
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


    ScreenSaverConfigFile screenSaverConfigFile(std::move(fileManager));

    VectorData fileData;

    auto result = screenSaverConfigFile.LoadConfiguration(fileData);

    EXPECT_FALSE(result);
}

INSTANTIATE_TEST_SUITE_P(readFileFailed, ScreenSaverConfigFileTestParam,
                         ::testing::Values("enable\"yes\"",

                                           "enable=\"yes\"\n\
timeout\"/home/music\"",

                                           "gfgfgf"));
