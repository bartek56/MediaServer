#ifndef SETTINGS_STATUS_H
#define SETTINGS_STATUS_H

#include "src/EditWifiConfigFile.h"
#include "src/EditAlarmConfigFile.h"

#include <QObject>
#include <memory>

class SettingsStatus : public QObject
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
    const QString FILEBROWSER_SERVICE = "filebrowser.service";
    const QString TRANSMISSION_SERVICE = "transmission-daemon.service";

    Q_OBJECT
public:
    explicit SettingsStatus(QObject *parent = nullptr);
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

    Q_INVOKABLE void updateNetworkStatus(QObject *obj);

    bool checkSystemdStatusExist(const QString &serviceName);
    bool checkSystemdStatusIsEnabled(const QString &serviceNames);
    bool checkSystemdStatusIsActive(const QString &serviceName);

private:
    void StatusSwitch_onClicked(const bool statusSwitchIsChecked, const QString &serviceName);
    void StatusButton_onClicked(QObject *statusButton, const QString statusButtonText, const QString &serviceName);
    void checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString &serviceName);
};

#endif// SETTINGS_H
