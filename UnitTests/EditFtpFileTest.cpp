#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/src/FtpConfigFile.h"


class openFtpFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;
    QString user1 = "krzysztof";
    QString user2 = "andrzej";
    virtual void SetUp()
    {
        location.push_back("/filesToTests/ftpd.passwd");
    }
};
/*
TEST_F(openFtpFileTest, fileHasTwoUsers)
{
    EditFtpConfigFile editFile;
    auto list = editFile.OpenUsersListFile(location);
    ASSERT_EQ(list.size(), 2);
}
*/
