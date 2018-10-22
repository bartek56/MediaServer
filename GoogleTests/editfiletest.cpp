#include "editfiletest.h"
#include <gtest/gtest.h>
#include "../MediaServerApp/editfile.h"

class openFileTest : public ::testing::Test {
public:
    QString location = "/etc/samba/smb.conf";

};

TEST_F(openFileTest, fileHasThreeMainConfigurations)
{
    EditFile editFile;
    auto configsVector = editFile.OpenFile(location);
    ASSERT_EQ(configsVector.size(), 3);
}

TEST_F(openFileTest, firstConfigurationHasEightOptions)
{
    EditFile editFile;
    auto configs = editFile.OpenFile(location);
    auto firstConfiguration = configs[0];
    ASSERT_EQ(firstConfiguration.configs.size(), 8);
}

TEST_F(openFileTest, firstConfigurationHasNameGlobal)
{
    EditFile editFile;
    auto configs = editFile.OpenFile(location);
    auto firstConfiguration = configs[0];
    ASSERT_EQ(firstConfiguration.name, "[GLOBAL]");
}
