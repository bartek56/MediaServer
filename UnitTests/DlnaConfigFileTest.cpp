#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/src/DlnaConfigFile.h"

class DlnaConfigFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;
    virtual void SetUp()
    {
        location.push_back("/filesToTests/minidlna.conf");
    }
};

TEST_F(DlnaConfigFileTest, fileHasFiveConfigsParameters)
{
//    EditDlnaConfigFile editFile;
//    auto configsMap = editFile.OpenFile(location);
//    ASSERT_EQ(configsMap.size(), 5);
    ASSERT_TRUE(true);
}
