#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/ConfigFile/DlnaConfigFile.h"
#include "Mock/MockFileManager.h"

class DlnaConfigFileTest : public ::testing::Test
{
};

TEST_F(DlnaConfigFileTest, readNotCall)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    DlnaConfigFile dlnaConfigFile(std::move(fileManager));

    EXPECT_CALL(*mockFileManager, read(testing::_)).Times(0);
}

TEST_F(DlnaConfigFileTest, configFileNotExist)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    DlnaConfigFile dlnaConfigFile(std::move(fileManager));

    EXPECT_CALL(*mockFileManager, read(testing::_)).Times(1).WillOnce(testing::Invoke([&](QString &) { return false; }));

    VectorData fileData;

    EXPECT_FALSE(dlnaConfigFile.LoadConfiguration(fileData));
    EXPECT_TRUE(fileData.empty());
}

TEST_F(DlnaConfigFileTest, readFileOneLine)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    QString checkData = "port=8200";

    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    DlnaConfigFile dlnaConfigFile(std::move(fileManager));

    VectorData fileData;

    auto result = dlnaConfigFile.LoadConfiguration(fileData);
    EXPECT_TRUE(result);
    EXPECT_EQ(fileData.size(), std::size_t(1));

    EXPECT_EQ(fileData[0].key.toStdString(), "port");
    EXPECT_EQ(fileData[0].value.toStdString(), "8200");
}

TEST_F(DlnaConfigFileTest, readwholeFile)
{
    MockFileManager* mockFileManager = new MockFileManager();
    std::unique_ptr<IFileManager> fileManager = std::unique_ptr<MockFileManager>(mockFileManager);

    QString checkData = "port=8200\n"
                        "media_dir=V,/mnt/video\n"
                        "media_dir=A,/mnt/audio\n"
                        "media_dir=P,/mnt/pictures\n"
                        "friendly_name=My DLNA Server\n"
                        "\n";

    EXPECT_CALL(*mockFileManager, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    DlnaConfigFile dlnaConfigFile(std::move(fileManager));

    VectorData fileData;

    auto result = dlnaConfigFile.LoadConfiguration(fileData);

    EXPECT_TRUE(result);

    EXPECT_EQ(fileData.size(), std::size_t(5));

    EXPECT_EQ(fileData.getValueByKey(QString("port")).toStdString(), "8200");
    EXPECT_EQ(fileData.getValueByKey(QString("media_dir=V")).toStdString(), "/mnt/video");
    EXPECT_EQ(fileData.getValueByKey(QString("media_dir=A")).toStdString(), "/mnt/audio");
    EXPECT_EQ(fileData.getValueByKey(QString("media_dir=P")).toStdString(), "/mnt/pictures");
    EXPECT_EQ(fileData.getValueByKey(QString("friendly_name")).toStdString(), "My DLNA Server");


    EXPECT_TRUE(fileData.setValueByKey(QString("port"), QString("8300")));

    auto it = fileData.begin();
    EXPECT_EQ(it->key.toStdString(), "port");
    EXPECT_EQ(it->value.toStdString(), "8300");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "media_dir=V");
    EXPECT_EQ(it->value.toStdString(), "/mnt/video");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "media_dir=A");
    EXPECT_EQ(it->value.toStdString(), "/mnt/audio");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "media_dir=P");
    EXPECT_EQ(it->value.toStdString(), "/mnt/pictures");

    it = std::next(it);
    EXPECT_EQ(it->key.toStdString(), "friendly_name");
    EXPECT_EQ(it->value.toStdString(), "My DLNA Server");
}

TEST_F(DlnaConfigFileTest, saveWholeFileData)
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

    DlnaConfigFile dlnaConfigFile(std::move(fileManager));

    VectorData fileData;

    fileData.push_back(ConfigData("port", "8300"));
    fileData.push_back(ConfigData("media_dir=V", "/mnt/video"));
    fileData.push_back(ConfigData("media_dir=A", "/mnt/audio"));
    fileData.push_back(ConfigData("media_dir=P", "/mnt/pictures"));
    fileData.push_back(ConfigData("friendly_name", "My DLNA Server"));


    auto result = dlnaConfigFile.SaveConfiguration(fileData);

    EXPECT_TRUE(result);

    QStringList list = savingData.split("\n");
    list.pop_back();// remove last empty QString - reason of split

    EXPECT_EQ(list.size(), 5);

    EXPECT_EQ(list[0].toStdString(), "port=8300");
    EXPECT_EQ(list[1].toStdString(), "media_dir=V,/mnt/video");
    EXPECT_EQ(list[2].toStdString(), "media_dir=A,/mnt/audio");
    EXPECT_EQ(list[3].toStdString(), "media_dir=P,/mnt/pictures");
    EXPECT_EQ(list[4].toStdString(), "friendly_name=My DLNA Server");
}


class DlnaConfigFileTestParam : public ::testing::TestWithParam<std::string>
{
};

TEST_P(DlnaConfigFileTestParam, readFileFailed)
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

    DlnaConfigFile dlnaConfigFile(std::move(fileManager));

    VectorData fileData;

    auto result = dlnaConfigFile.LoadConfiguration(fileData);

    EXPECT_FALSE(result);
}

INSTANTIATE_TEST_SUITE_P(readFileFailed, DlnaConfigFileTestParam,
                         ::testing::Values("port,8300",

                                           "port=8300\n\
media_dir=/mnt/video",

                                           "friendly_name,dfdf"));

