#ifndef SETTINGS_H
#define SETTINGS_H

#include "../editwificonfigfile.h"
#include "../editalarmconfigfile.h"
#include "../editheadersconfigfile.h"

#include <QProcess>
#include <QtQuick>
#include <QObject>
#include <memory>

class Settings : public QObject
{

public:
    const QString TVHEADEND_SERVICE = "tvheadend.service";
    const QString WPASUPPLICANT_SERVICE = "wpa_supplicant.service";
    const QString YMPD_SERVICE = "ympd.service";
    const QString MPD_SERVICE = "mpd.service";
    const QString MINIDLNA_SERVICE = "minidlna.service";
    const QString SMB_SERVICE = "smb.service";
    const QString NMB_SERVICE = "nmb.service";
    const QString VSFTPD_SERVICE = "vsftpd.service";
    const QString FILEBROWSER_SERVICE = "fileBrowser.service";
    const QString TRANSMISSION_SERVICE = "transmission-daemon.service";

    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);

    // Wifi
    Q_INVOKABLE void searchNetworks(QObject* obj);
    Q_INVOKABLE void updateWifiStatus(QObject* obj);
    Q_INVOKABLE void updateNetworkStatus(QObject* obj);
    Q_INVOKABLE void connect(const QString networkName, const QString password);
    Q_INVOKABLE void loadWifiConfigFile();
    Q_INVOKABLE void cbNetworks_onDisplayTextChanged(QString networkName, QObject *obj);
    Q_INVOKABLE void sWifiOn_OnCheckedChanged(bool wifiOnSwitch);
    Q_INVOKABLE void checkWifi(QObject *obj);


    // IP Address
    Q_INVOKABLE void loadIpAddressConfiguration(const int networkInterfaceIndexComboBox, QObject* dynamicIPRadioButton,
                                                QObject* staticIPRadioButton, QObject* ipadressTextField,
                                                QObject* netmaskTextField, QObject* gatewayTextField,
                                                QObject* dnsserverTextField);
    Q_INVOKABLE void tfIpAddress_onEditingFinished(const QString text);
    Q_INVOKABLE void tfNetMask_onEditingFinished(const QString text);
    Q_INVOKABLE void tfGateway_onEditingFinished(const QString text);
    Q_INVOKABLE void tfDNSServer_onEditingFinished(const QString text);
    Q_INVOKABLE void rbDynamicIP_onClicked();
    Q_INVOKABLE void rbStaticIP_onClicked(const QString ipadressTextField, const QString netmaskTextField,
                                          const QString gatewayTextField, const QString dnsserverTextField);
    Q_INVOKABLE void saveIpAddressConfiguration();

    //Systemd services
    Q_INVOKABLE void checkTvHeadEndServiceStatus(QObject *tvHeadEndStatusSwitch, QObject *TvHeadEndStatusButton);
    Q_INVOKABLE void tvHeadEndStatusSwitch_OnClicked(const bool tvHeadEndStatusSwitchIsChecked);
    Q_INVOKABLE void tvHeadEndStatusButton_OnClicked(QObject *tvHeadEndStatusButton, const QString tvHeadEndStatusButtonText);

    Q_INVOKABLE void checkYMPDSystemdStatus(QObject *ympdStatusSwitch, QObject *ympdStatusButton);
    Q_INVOKABLE void ympdStatusSwitch_OnClicked(const bool ympdStatusSwitchIsChecked);
    Q_INVOKABLE void ympdStatusButton_OnClicked(QObject *ympdStatusButton, const QString ympdStatusButtonText);

    Q_INVOKABLE void checkMPDSystemdStatus(QObject *mpdStatusSwitch, QObject *mpdStatusButton);
    Q_INVOKABLE void mpdStatusSwitch_OnClicked(const bool mpdStatusSwitchIsChecked);
    Q_INVOKABLE void mpdStatusButton_OnClicked(QObject *mpdStatusButton, const QString mpdStatusButtonText);

    Q_INVOKABLE void checkDLNASystemdStatus(QObject *dlnaStatusSwitch, QObject *dlnaStatusButton);
    Q_INVOKABLE void dlnaStatusSwitch_OnClicked(const bool dlnaStatusSwitchIsChecked);
    Q_INVOKABLE void dlnaStatusButton_OnClicked(QObject *dlnaStatusButton, const QString dlnaStatusButtonText);

    Q_INVOKABLE void checkSMBSystemdStatus(QObject *smbStatusSwitch, QObject *smbStatusButton);
    Q_INVOKABLE void sambaStatusSwitch_OnClicked(const bool sambaStatusSwitchIsChecked);
    Q_INVOKABLE void sambaStatusButton_OnClicked(QObject *sambaStatusButton, const QString sambaStatusButtonText);

    Q_INVOKABLE void checkFTPSystemdStatus(QObject *ftpStatusSwitch, QObject *ftpStatusButton);
    Q_INVOKABLE void ftpStatusSwitch_OnClicked(const bool ftpStatusSwitchIsChecked);
    Q_INVOKABLE void ftpStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText);

    Q_INVOKABLE void checkFileBrowserSystemdStatus(QObject *fileBrowserStatusSwitch, QObject *fileBrowserStatusButton);
    Q_INVOKABLE void fileBrowserStatusSwitch_OnClicked(const bool fileBrowserStatusSwitchIsChecked);
    Q_INVOKABLE void fileBrowserStatusButton_OnClicked(QObject *fileBrowserStatusButton, const QString fileBrowserStatusButtonText);

    Q_INVOKABLE void checkTorrentClientSystemdStatus(QObject *torrentClientStatusSwitch, QObject *torrentCLientStatusButton);
    Q_INVOKABLE void torrentClientStatusSwitch_OnClicked(const bool torrentClientStatusSwitchIsChecked);
    Q_INVOKABLE void torrentClientStatusButton_OnClicked(QObject *torrentClientStatusButton, const QString torrentClientStatusButtonText);

    bool checkSystemdStatusExist(const QString &serviceName);
    bool checkSystemdStatusIsEnabled(const QString &serviceNames);
    bool checkSystemdStatusIsActive(const QString &serviceName);

private:
    // IP Adress
    const QString ETHERNET_CONFIG_FILE="/etc/mediaserver/10-wired.network";
    const QString WIFI_CONFIG_FILE="/etc/mediaserver/20-wireless.network";

    std::unique_ptr<EditHeadersConfigFile> wifiIpAddressConfigFile;
    std::unique_ptr<EditHeadersConfigFile> ethernetIpAddressConfigFile;

    std::shared_ptr<std::vector<HeadersConfig>> vEtnernetIpAddressConfigsPtr;
    std::shared_ptr<std::vector<HeadersConfig>> vWifiIpAddressConfigsPtr;
    std::shared_ptr<std::vector<HeadersConfig>> vIpAddressConfigsPtr;

    QStringList splitString(const QString &str, int n);
    QString binToDec(QString bin);
    QString decToBin(QString dev);
    QString convertNetMaskToFull(QString decMask);
    QString convertNetMaskToShort(QString decMask);

    void setCurrentIpAddressConfig(const int &networkInterfaceComboboxIndex);

    // Wifi Config
    QObject* bConnect;
    QObject* bScanNetwork;
    bool wifiIsOn;

    EditWifiConfigFile editWifiConfigFile;
    std::vector<WifiConfigsName> vWifiConfigs;

    void StatusSwitch_onClicked(const bool statusSwitchIsChecked, const QString &serviceName);
    void StatusButton_onClicked(QObject *statusButton, const QString statusButtonText, const QString &serviceName);
    void checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString nameservice);

};

#endif // SETTINGS_H
