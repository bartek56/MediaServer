#ifndef MPDCONFIG_H
#define MPDCONFIG_H

#include <QtQuick>
#include <QObject>
#include "Utils/VectorData.h"
#include "ConfigFile/AlarmConfigFile.h"

class AlarmConfig : public QObject
{
private:
    const QString ALARM_TIMER = "alarm.timer";
    const QString ALARM_SNOOZE_TIMER = "alarm_snooze.timer";
    const QString ALARM_SERVICE = "alarm.service";
    const QString BASH = "bash";

    bool systemdAlarmSupport = false;
    bool configFileValidate = false;
    bool alarmIsEnabled = false;

    QStringList loadMPDPlaylists();
    QProcess testAlarmProcess;
    VectorData mAlarmConfigs;
    AlarmConfigFile editAlarmConfigFile;
    bool saveAlarmIsSystemdTimer(const QString &daysOfWeek, const QString &time);
    bool checkAlarmIsActive();
    bool checkAlarmSnoozeIsActive();

    Q_OBJECT
public:
    explicit AlarmConfig(QObject *parent = nullptr);

    Q_INVOKABLE void loadAlarmConfigurations(QObject *minVolumeSpinBox, QObject *maxVolumeSpinBox, QObject *defaultVolumeSpinBox, QObject *growingVolumeSpinBox, QObject *growingSpeedSpinBox,
                                             QObject *isNewestSongsListRadioButton, QObject *isPlaylistRadioButton, QObject *playlistComboBox, QObject *testButton);
    Q_INVOKABLE void loadAlarmService(QObject *monCheckBox, QObject *tueCheckBox, QObject *wedCheckBox, QObject *thuCheckBox, QObject *friCheckBox, QObject *satCheckBox, QObject *sunCheckBox,
                                      QObject *timeHHSpinBox, QObject *timeMMSpinBox);
    Q_INVOKABLE void checkAlarmService(QObject *enableAlarmSwitch);
    Q_INVOKABLE void switchEnableAlarm_onClicked(const bool isEnable);
    Q_INVOKABLE void bStartTestAlarm_onClicked();
    Q_INVOKABLE void bStopTestAlarm_onClicked();
    Q_INVOKABLE void bStopSnooze_onClicked();

    Q_INVOKABLE void bSaveAlarm_onClicked(const int minVolume, const int maxVolume, const int defaultVolume, const int growingVolume, const int growingSpeed, const bool isNewestSongsList,
                                          const QString playlist);
    Q_INVOKABLE void bSaveAlarmService_onClicked(const bool monCheckBox, const bool tueCheckBox, const bool wedCheckBox, const bool thuCheckBox, const bool friCheckBox, const bool satCheckBox,
                                                 const bool sunCheckBox, const int timeHHSpinBox, const int timeMMSpinBox);

    Q_PROPERTY(bool systemdSupportExist READ isSystemdSupport)
    Q_PROPERTY(bool configFileExist READ isConfigFileExist)
    Q_PROPERTY(bool configFileValidated READ isConfigFileValidated)
    bool isSystemdSupport() const;
    bool isConfigFileExist() const;
    bool isConfigFileValidated() const;

public slots:
};

#endif// MPDCONFIG_H
