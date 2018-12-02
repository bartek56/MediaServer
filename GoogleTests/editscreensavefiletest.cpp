#include "editfiletest.h"
#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerApp/editscreensaverconfigfile.h"

class openScreenSaverConfigFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;
    virtual void SetUp()
    {
        location.push_back("/filesToTests/startScreensaver.sh");
    }
};

TEST_F(openScreenSaverConfigFileTest, fileHasThreeConfigsParameters)
{
    EditScreenSaverConfigFile editFile;
    auto configsMap = editFile.LoadConfiguration(location);
    ASSERT_EQ(configsMap.size(), 3);
}
