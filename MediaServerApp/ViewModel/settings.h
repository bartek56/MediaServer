#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QProcess>
#include <memory>
#include <QtQuick>
#include "editwificonfigfile.h"
#include "editscreensaverconfigfile.h"
#include "editalarmconfigfile.h"


class Settings : public QObject
{

public:
    const QString TVHEADEND_SERVICE = "tvheadend.service";
    const QString WPASUPPLICANT_SERVICE = "wpa_supplicant.service";
    const QString YMPD_SERVICE = "ympd.service";
    const QString MPD_SERVICE = "mpd.service";
    const QString MINIDLNA_SERVICE = "minidlnad.service";
    const QString SMB_SERVICE = "smb.service";
    const QString NMB_SERVICE = "nmb.service";
    const QString VSFTPD_SERVICE = "vsftpd.service";
    const QString FILEBROWSER_SERVICE = "fileBrowser.service";
    const QString TRANSMISSION_SERVICE = "transmission-daemon.service";

    const QString WPASUPPLICANT_CONF = "/etc/wpa_supplicant.conf";
    const QString SCREENSAVER_SCRIPT = "/opt/startScreensaver.sh";



    const QString SYSTEMD_SYSTEM_PATH="/lib/systemd/system";

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

    // ScreenSaver
    Q_INVOKABLE void bScreenSaverFileDialog_onAccepted(QString folderPath, QObject *tfScreenSavrFolderPath);
    Q_INVOKABLE void bSaveScreenSaver_onClicked(const QString timeout, const QString path, const int startTime,const bool random);
    Q_INVOKABLE void loadScreenSaverConfigurations(QObject *startTime, QObject *path, QObject *timeout,QObject *random);


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


signals:

public slots:

private:
    EditWifiConfigFile editWifiConfigFile;
    EditScreenSaverConfigFile editScreenSaverConfigFile;
    std::vector<WifiConfigsName> vWifiConfigs;
    std::map<QString, QString> mScreenSaverConfigs;

    QObject* bConnect;
    QObject* bScanNetwork;
    bool wifiIsOn;

    bool checkSystemdStatusExist(const QString &serviceName);
    bool checkSystemdStatusIsEnabled(const QString &serviceNames);
    bool checkSystemdStatusIsActive(const QString &serviceName);
    void StatusSwitch_onClicked(const bool statusSwitchIsChecked, const QString &serviceName);
    void StatusButton_onClicked(QObject *statusButton, const QString statusButtonText, const QString &serviceName);
    void checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString nameservice);

    int ConvertTimeFromMiliSecStringToMinutesInt(QString milisec);
};

#endif // SETTINGS_H
