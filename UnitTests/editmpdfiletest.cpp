#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/src/editmpdconfigfile.h"
#include "Mock/mockfilemanager.cpp"

class openMpdConfigFileTest : public ::testing::Test {
};

TEST_F(openMpdConfigFileTest, readFile)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    EditMpdConfigFile editMpdConfigFile(mockReadFile);

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(0);
}

TEST_F(openMpdConfigFileTest, readFile1)
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

    auto result = editMpdConfigFile.OpenFile();
    EXPECT_EQ(result.cbegin()->first.toStdString(), "playlistdir");
    EXPECT_EQ(result.cbegin()->second.toStdString(), "/home/playlistdir");

}
