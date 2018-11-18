#include "editfiletest.h"
#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerApp/editdlnaconfigfile.h"

class openDlnaConfigFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;
    virtual void SetUp()
    {
        location.push_back("/filesToTests/minidlna.conf");
    }
};

TEST_F(openDlnaConfigFileTest, fileHasFiveConfigsParameters)
{
    EditDlnaConfigFile editFile;
    auto configsMap = editFile.OpenFile(location);
    ASSERT_EQ(configsMap.size(), 5);
}
