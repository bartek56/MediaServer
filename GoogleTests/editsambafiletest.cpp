#include "editfiletest.h"
#include <gtest/gtest.h>
#include <QDebug>
#include "../MediaServerApp/editsambaconfigfile.h"

class openSambaFileTest : public ::testing::Test {
public:
    QString location=PATH_TO_TEST_FILES;

    virtual void SetUp()
    {
        location.push_back("/filesToTests/smb.conf");
    }
};

TEST_F(openSambaFileTest, fileHasThreeMainConfigurations)
{
    EditSambaConfigFile editFile;
    auto configsVector = editFile.OpenFile(location);
    ASSERT_EQ(configsVector.size(), 3);
}

TEST_F(openSambaFileTest, firstConfigurationHasEightOptions)
{
    EditSambaConfigFile editFile;
    auto configs = editFile.OpenFile(location);
    auto firstConfiguration = configs[0];
    ASSERT_EQ(firstConfiguration.configs.size(), 8);
}

TEST_F(openSambaFileTest, firstConfigurationHasNameGlobal)
{
    EditSambaConfigFile editFile;
    auto configs = editFile.OpenFile(location);
    auto firstConfiguration = configs[0];
    ASSERT_EQ(firstConfiguration.name, "[GLOBAL]");
}

