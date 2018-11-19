#include "editfiletest.h"
#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerApp/editmpdconfigfile.h"

class openMpdConfigFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;
    virtual void SetUp()
    {
        location.push_back("/filesToTests/mpd.conf");
    }
};

TEST_F(openMpdConfigFileTest, fileHasFiveConfigsParameters)
{
    EditMpdConfigFile editFile;
    auto configsMap = editFile.OpenFile(location);
    ASSERT_EQ(configsMap.size(), 7);
}
