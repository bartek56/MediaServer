#include "../MediaServerLib/ConfigFile/WifiConfigFile.h"
#include "Mock/MockFileManager.h"

#include <gtest/gtest.h>
#include <QStringList>

class WifiConfigFileTest : public ::testing::Test
{
};


TEST_F(WifiConfigFileTest, readNotCall)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    WifiConfigFile wifiConfigFile(mockReadFile);

    EXPECT_CALL(*mockReadFile, read(testing::_)).Times(0);
}

TEST_F(WifiConfigFileTest, configFileNotExist)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    EXPECT_CALL(*mockReadFile, read(testing::_)).Times(1).WillOnce(testing::Invoke([&](QString &) { return false; }));

    WifiConfigFile wifiConfigFile(mockReadFile);

    std::vector<VectorData> ssidConfig;
    VectorData globalConfig;


    auto result = wifiConfigFile.LoadConfiguration(globalConfig, ssidConfig);

    EXPECT_FALSE(result);
}


TEST_F(WifiConfigFileTest, readFileOneSSID)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData = "network={\n"
                        "psk=\"hardpassword\"\n"
                        "ssid=\"wifiname\"\n"
                        "}\n"
                        "\n"
                        "\n"
                        "\n";

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    WifiConfigFile wifiConfigFile(mockReadFile);

    std::vector<VectorData> ssidData;
    VectorData wificonfigs;

    auto result = wifiConfigFile.LoadConfiguration(wificonfigs, ssidData);
    EXPECT_TRUE(result);

    // wifiConfigs
    EXPECT_EQ(wificonfigs.size(), std::size_t(0));


    // ssid
    EXPECT_EQ(ssidData.size(), std::size_t(1));

    auto vNetworkData = ssidData[0];

    EXPECT_EQ(vNetworkData.size(), std::size_t(2));

    EXPECT_EQ(vNetworkData[0].key.toStdString(), "psk");
    EXPECT_EQ(vNetworkData[0].value.toStdString(), "hardpassword");
    EXPECT_EQ(vNetworkData[1].key.toStdString(), "ssid");
    EXPECT_EQ(vNetworkData[1].value.toStdString(), "wifiname");
}

TEST_F(WifiConfigFileTest, readFileOneSSIDAndGlobalConfigs)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData = "ctrl_interface=/var/run/wpa_supplicant\n"
                        "ap_scan=1"
                        "\n"
                        "\n"
                        "\n"
                        "network={\n"
                        "psk=\"hardpassword\"\n"
                        "ssid=\"wifiname\"\n"
                        "}\n"
                        "\n"
                        "\n"
                        "\n";

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    WifiConfigFile wifiConfigFile(mockReadFile);

    std::vector<VectorData> ssidData;
    VectorData wificonfigs;

    auto result = wifiConfigFile.LoadConfiguration(wificonfigs, ssidData);
    EXPECT_TRUE(result);

    // wifiConfigs
    EXPECT_EQ(wificonfigs.size(), std::size_t(2));
    EXPECT_EQ(wificonfigs[0].key.toStdString(), "ctrl_interface");
    EXPECT_EQ(wificonfigs[0].value.toStdString(), "/var/run/wpa_supplicant");
    EXPECT_EQ(wificonfigs[1].key.toStdString(), "ap_scan");
    EXPECT_EQ(wificonfigs[1].value.toStdString(), "1");


    // ssid
    EXPECT_EQ(ssidData.size(), std::size_t(1));

    auto vNetworkData = ssidData[0];

    EXPECT_EQ(vNetworkData.size(), std::size_t(2));

    EXPECT_EQ(vNetworkData[0].key.toStdString(), "psk");
    EXPECT_EQ(vNetworkData[0].value.toStdString(), "hardpassword");
    EXPECT_EQ(vNetworkData[1].key.toStdString(), "ssid");
    EXPECT_EQ(vNetworkData[1].value.toStdString(), "wifiname");
}

TEST_F(WifiConfigFileTest, readFileTwoSSIDAndGlobalConfigs)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString checkData = "ctrl_interface=/var/run/wpa_supplicant\n"
                        "ap_scan=1"
                        "\n"
                        "\n"
                        "\n"
                        "network={\n"
                        "psk=\"hardpassword_1\"\n"
                        "ssid=\"wifiname_1\"\n"
                        "}\n"
                        "\n"
                        "\n"
                        "network={\n"
                        "psk=\"hardpassword_2\"\n"
                        "ssid=\"wifiname_2\"\n"
                        "}\n"
                        "\n"
                        "\n"
                        "\n"
                        "\n";

    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = checkData;
                        return true;
                    }));

    WifiConfigFile wifiConfigFile(mockReadFile);

    std::vector<VectorData> ssidData;
    VectorData wificonfigs;

    auto result = wifiConfigFile.LoadConfiguration(wificonfigs, ssidData);
    EXPECT_TRUE(result);

    // wifiConfigs
    EXPECT_EQ(wificonfigs.size(), std::size_t(2));
    EXPECT_EQ(wificonfigs[0].key.toStdString(), "ctrl_interface");
    EXPECT_EQ(wificonfigs[0].value.toStdString(), "/var/run/wpa_supplicant");
    EXPECT_EQ(wificonfigs[1].key.toStdString(), "ap_scan");
    EXPECT_EQ(wificonfigs[1].value.toStdString(), "1");


    // ssid
    EXPECT_EQ(ssidData.size(), std::size_t(2));

    const VectorData vNetworkData1 = ssidData[0];

    EXPECT_EQ(vNetworkData1.size(), std::size_t(2));

    EXPECT_EQ(vNetworkData1[0].key.toStdString(), "psk");
    EXPECT_EQ(vNetworkData1[0].value.toStdString(), "hardpassword_1");
    EXPECT_EQ(vNetworkData1[1].key.toStdString(), "ssid");
    EXPECT_EQ(vNetworkData1[1].value.toStdString(), "wifiname_1");

    const VectorData vNetworkData2 = ssidData[1];
    EXPECT_EQ(vNetworkData2.size(), std::size_t(2));

    EXPECT_EQ(vNetworkData2[0].key.toStdString(), "psk");
    EXPECT_EQ(vNetworkData2[0].value.toStdString(), "hardpassword_2");
    EXPECT_EQ(vNetworkData2[1].key.toStdString(), "ssid");
    EXPECT_EQ(vNetworkData2[1].value.toStdString(), "wifiname_2");
}


TEST_F(WifiConfigFileTest, saveConfigData)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    QString savingData;

    EXPECT_CALL(*mockReadFile, save(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](const QString &fileData)
                    {
                        savingData = fileData;
                        return true;
                    }));

    WifiConfigFile wifiConfigFile(mockReadFile);

    VectorData globalData;
    globalData.push_back(ConfigData("ctrl_interface", "/var/run/wpa_supplicant"));
    globalData.push_back(ConfigData("ap_scan", "1"));

    VectorData net1;
    net1.push_back(ConfigData("psk", "hardpassword_1"));
    net1.push_back(ConfigData("ssid", "wifiname_1"));
    VectorData net2;
    net2.push_back(ConfigData("psk", "hardpassword_2"));
    net2.push_back(ConfigData("ssid", "wifiname_2"));

    std::vector<VectorData> ssidConfig = {net1, net2};


    auto result = wifiConfigFile.SaveConfiguration(globalData, ssidConfig);
    EXPECT_TRUE(result);

    QStringList list = savingData.split("\n");
    list.pop_back();// remove last empty QString - reason of split
    EXPECT_EQ(list.size(), 10);

    EXPECT_EQ(list[0].toStdString(), "ctrl_interface=/var/run/wpa_supplicant");
    EXPECT_EQ(list[1].toStdString(), "ap_scan=1");
    EXPECT_EQ(list[2].toStdString(), "network={");
    EXPECT_EQ(list[3].toStdString(), "psk=\"hardpassword_1\"");
    EXPECT_EQ(list[4].toStdString(), "ssid=\"wifiname_1\"");
    EXPECT_EQ(list[5].toStdString(), "}");
    EXPECT_EQ(list[6].toStdString(), "network={");
    EXPECT_EQ(list[7].toStdString(), "psk=\"hardpassword_2\"");
    EXPECT_EQ(list[8].toStdString(), "ssid=\"wifiname_2\"");
    EXPECT_EQ(list[9].toStdString(), "}");
}


class WifiConfigFileTestParam : public ::testing::TestWithParam<std::string>
{
};

TEST_P(WifiConfigFileTestParam, readFileFailed)
{
    std::shared_ptr<MockFileManager> mockReadFile = std::make_shared<MockFileManager>();

    auto param = GetParam();
    EXPECT_CALL(*mockReadFile, read(testing::_))
            .Times(1)
            .WillOnce(testing::Invoke(
                    [&](QString &fileData)
                    {
                        fileData = QString::fromStdString(param);
                        return true;
                    }));

    WifiConfigFile wifiConfigFile(mockReadFile);

    std::vector<VectorData> ssidConfig;
    VectorData globalConfig;


    auto result = wifiConfigFile.LoadConfiguration(globalConfig, ssidConfig);

    EXPECT_FALSE(result);
}

INSTANTIATE_TEST_SUITE_P(readFileFailed, WifiConfigFileTestParam,
                         ::testing::Values("ap_scan\"yes\"",

                                           "ap_scan=1\n"
                                           "network={}",

                                           "test"));
