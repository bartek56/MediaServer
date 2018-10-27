#include "editfiletest.h"
#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerApp/editftpconfigfile.h"

class openFtpFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;

    virtual void SetUp()
    {
        location.push_back("/filesToTests/ftpd.passwd");
    }
};

TEST_F(openFtpFileTest, fileHasTwoUsers)
{
    EditFtpConfigFile editFile;
    auto list = editFile.OpenFile(location);
    ASSERT_EQ(list.size(), 2);
}

