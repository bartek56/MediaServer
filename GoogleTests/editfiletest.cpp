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
    auto configsVector = editFile.OpenFile(location);
    ASSERT_EQ(configsVector.size(), 3);
}

TEST_F(editFileTest, firstConfigurationHasEightOptions)
{
    EditFile editFile;
    auto configs = editFile.OpenFile(location);
    auto firstConfiguration = configs[0];
    ASSERT_EQ(firstConfiguration.configs.size(), 8);
}

TEST_F(editFileTest, firstConfigurationHasNameGlobal)
{
    EditFile editFile;
    auto configs = editFile.OpenFile(location);
    auto firstConfiguration = configs[0];
    ASSERT_EQ(firstConfiguration.name, "[GLOBAL]");
}
