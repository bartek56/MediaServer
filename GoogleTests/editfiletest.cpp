#include "editfiletest.h"
#include <gtest/gtest.h>
#include "../MediaServerApp/editfile.h"

class editFileTest : public ::testing::Test {
public:
    QString location = "/etc/samba/smb.conf";

};

TEST_F(editFileTest, fileHasThreeMainConfigurations)
{
    EditFile editFile;
    auto configMap = editFile.OpenFile(location);
    ASSERT_EQ(configMap.size(), 3);
}

TEST_F(editFileTest, firstConfigurationHasEightOptions)
{
    EditFile editFile;
    auto configMap = editFile.OpenFile(location);
    auto firstConfiguration = configMap.at("[GLOBAL]");
    ASSERT_EQ(firstConfiguration.size(), 8);
}
