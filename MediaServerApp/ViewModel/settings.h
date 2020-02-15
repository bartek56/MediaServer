#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QProcess>
#include <memory>
#include <QtQuick>
#include "editwificonfigfile.h"
#include "editscreensaverconfigfile.h"
#include "editalarmconfigfile.h"
#include "managementofexternaldevices.h"
#include "managementfatdrive.h"
#include "managementntfsdrive.h"


class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);

    Q_INVOKABLE void searchNetworks(QObject* obj);
    Q_INVOKABLE void updateWifiStatus(QObject* obj);
    Q_INVOKABLE void updateNetworkStatus(QObject* obj);
    Q_INVOKABLE void connect(const QString networkName, const QString password);
    Q_INVOKABLE void loadWifiConfigFile();
    Q_INVOKABLE void cbNetworks_onDisplayTextChanged(QString networkName, QObject *obj);
    Q_INVOKABLE void sWifiOn_OnCheckedChanged(bool wifiOnSwitch);
    Q_INVOKABLE void checkWifi(QObject *obj);

    Q_INVOKABLE void loadExternalDevices(QObject *devicesList, QObject *mountButton);
    Q_INVOKABLE void cbDevices_onDisplayTextChanged(QString deviceName, QObject *deviceSizeText, QObject *nameDeviceText, QObject *mountPointText, QObject *typeText);
    Q_INVOKABLE void bMount_onClicked(const QString mountpoint,const QString deviceName, QString deviceLabel, const bool automount, const QString type);

    Q_INVOKABLE void loadAlarmConfigurations(QObject *minVolumeSpinBox, QObject *maxVolumeSpinBox, QObject *growingVolumeSpinBox, QObject *growingSpeedSpinBox, QObject *isNewestSongsListRadioButton, QObject *isPlaylistRadioButton, QObject *playlistComboBox);
    Q_INVOKABLE void loadAlarmService(QObject *monCheckBox, QObject *tueCheckBox, QObject *wedCheckBox, QObject *thuCheckBox, QObject *friCheckBox, QObject *satCheckBox, QObject *sunCheckBox, QObject *timeHHSpinBox, QObject *timeMMSpinBox);
    Q_INVOKABLE void checkAlarmService(QObject *enableAlarmSwitch);
    Q_INVOKABLE void switchEnableAlarm_onClicked(const bool isEnable);
    Q_INVOKABLE void bStartTestAlarm_onClicked();
    Q_INVOKABLE void bStopTestAlarm_onClicked();
    Q_INVOKABLE void bSaveAlarm_onClicked(const int minVolume, const int maxVolume, const int growingVolume, const int growingSpeed, const bool isNewestSongsList, const QString playlist);
    Q_INVOKABLE void bSaveAlarmService_onClicked(const bool monCheckBox, const bool tueCheckBox, const bool wedCheckBox, const bool thuCheckBox, const bool friCheckBox, const bool satCheckBox, const bool sunCheckBox, const int timeHHSpinBox, const int timeMMSpinBox);


    Q_INVOKABLE void bScreenSaverFileDialog_onAccepted(QString folderPath, QObject *tfScreenSavrFolderPath);
    Q_INVOKABLE void bSaveScreenSaver_onClicked(const QString timeout, const QString path, const int startTime,const bool random);
    Q_INVOKABLE void loadScreenSaverConfigurations(QObject *startTime, QObject *path, QObject *timeout,QObject *random);

    Q_INVOKABLE void checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString nameservice);

    Q_INVOKABLE void tvHeadEndStatusSwitch_OnClicked(const bool tvHeadEndStatusSwitchIsChecked, QObject *tvHeadEndStatusButton);
    Q_INVOKABLE void tvHeadEndStatusButton_OnClicked(QObject *tvHeadEndStatusButton, const QString tvHeadEndStatusButtonText);
    Q_INVOKABLE void ympdStatusSwitch_OnClicked(const bool ympdStatusSwitchIsChecked, QObject *ympdStatusButton);
    Q_INVOKABLE void ympdStatusButton_OnClicked(QObject *ympdStatusButton, const QString ympdStatusButtonText);
    Q_INVOKABLE void mpdStatusSwitch_OnClicked(const bool mpdStatusSwitchIsChecked, QObject *mpdStatusButton);
    Q_INVOKABLE void mpdStatusButton_OnClicked(QObject *mpdStatusButton, const QString mpdStatusButtonText);
    Q_INVOKABLE void dlnaStatusSwitch_OnClicked(const bool dlnaStatusSwitchIsChecked, QObject *dlnaStatusButton);
    Q_INVOKABLE void dlnaStatusButton_OnClicked(QObject *dlnaStatusButton, const QString dlnaStatusButtonText);
    Q_INVOKABLE void sambaStatusSwitch_OnClicked(const bool sambaStatusSwitchIsChecked, QObject *sambaStatusButton);
    Q_INVOKABLE void sambaStatusButton_OnClicked(QObject *sambaStatusButton, const QString sambaStatusButtonText);
    Q_INVOKABLE void ftpStatusSwitch_OnClicked(const bool ftpStatusSwitchIsChecked, QObject *ftpStatusButton);
    Q_INVOKABLE void ftpStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText);
    Q_INVOKABLE void fileBrowserStatusSwitch_OnClicked(const bool fileBrowserStatusSwitchIsChecked, QObject *fileBrowserStatusButton);
    Q_INVOKABLE void fileBrowserStatusButton_OnClicked(QObject *fileBrowserStatusButton, const QString fileBrowserStatusButtonText);
    Q_INVOKABLE void torrentClientStatusSwitch_OnClicked(const bool torrentClientStatusSwitchIsChecked, QObject *torrentClientStatusButton);
    Q_INVOKABLE void torrentClientStatusButton_OnClicked(QObject *torrentClientStatusButton, const QString torrentClientStatusButtonText);

    Q_INVOKABLE void shutdownButton_OnClicked();

signals:

public slots:

private:
    EditWifiConfigFile editWifiConfigFile;
    EditScreenSaverConfigFile editScreenSaverConfigFile;
    EditAlarmConfigFile editAlarmConfigFile;
    ManagementOfExternalDevices *managementExternalDevices;
    std::vector<WifiConfigsName> vWifiConfigs;
    std::map<QString, QString> mScreenSaverConfigs;
    std::map<QString, QString> mAlarmConfigs;
    QProcess testAlarmProcess;
    int ConvertTimeFromMiliSecStringToMinutesInt(QString milisec);
    QObject* bConnect;
    QObject* bScanNetwork;
    bool wifiIsOn;
    bool checkSystemdStatusExist(const QString &serviceName);
    bool checkSystemdStatusIsEnabled(const QString &serviceNames);
    bool checkSystemdStatusIsActive(const QString &serviceName);
    void StatusSwitch_onClicked(const bool statusSwitchIsChecked, QObject *statusButton, const QString &serviceName);
    void StatusButton_onClicked(QObject *statusButton, const QString statusButtonText, const QString &serviceName);
    void saveAlarmIsSystemdTimer(const QString &daysOfWeek, const QString &time);
};

#endif // SETTINGS_H
