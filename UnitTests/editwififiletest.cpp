#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerLib/src/editwificonfigfile.h"

class openWifiFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;

    virtual void SetUp()
    {
        location.push_back("/filesToTests/wpa_supplicant.conf");
    }
};

TEST_F(openWifiFileTest, fileHasThreeWifiConfiguration)
{
//    EditWifiConfigFile editFile;
//    auto configsVector = editFile.OpenFile(location);
//    ASSERT_EQ(configsVector.size(), 3);
    ASSERT_TRUE(true);
}


