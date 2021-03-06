#ifndef MPDCONFIG_H
#define MPDCONFIG_H

#include <QtQuick>
#include <QObject>
#include "editalarmconfigfile.h"

class AlarmConfig : public QObject
{
private:
    const QString CONFIG_PATH = "/etc/mediaserver";
    const QString ALARM_SCRIPT = CONFIG_PATH+"/alarm.sh";

    const QString ALARM_TIMER = "alarm.timer";
    const QString ALARM_SERVICE = "alarm.service";
    const QString BASH = "bash";

    QStringList loadMPDPlaylists();
    QProcess testAlarmProcess;
    std::map<QString, QString> mAlarmConfigs;
    EditAlarmConfigFile editAlarmConfigFile;
    void saveAlarmIsSystemdTimer(const QString &daysOfWeek, const QString &time);
    bool checkAlarmIsActive();

    Q_OBJECT
public:
    explicit AlarmConfig(QObject *parent = nullptr);

    Q_INVOKABLE void loadAlarmConfigurations(QObject *minVolumeSpinBox, QObject *maxVolumeSpinBox, QObject *defaultVolumeSpinBox, QObject *growingVolumeSpinBox, QObject *growingSpeedSpinBox, QObject *isNewestSongsListRadioButton, QObject *isPlaylistRadioButton, QObject *playlistComboBox);
    Q_INVOKABLE void loadAlarmService(QObject *monCheckBox, QObject *tueCheckBox, QObject *wedCheckBox, QObject *thuCheckBox, QObject *friCheckBox, QObject *satCheckBox, QObject *sunCheckBox, QObject *timeHHSpinBox, QObject *timeMMSpinBox);
    Q_INVOKABLE void checkAlarmService(QObject *enableAlarmSwitch);
    Q_INVOKABLE void switchEnableAlarm_onClicked(const bool isEnable);
    Q_INVOKABLE void bStartTestAlarm_onClicked();
    Q_INVOKABLE void bStopTestAlarm_onClicked();
    Q_INVOKABLE void bSaveAlarm_onClicked(const int minVolume, const int maxVolume, const int defaultVolume, const int growingVolume, const int growingSpeed, const bool isNewestSongsList, const QString playlist);
    Q_INVOKABLE void bSaveAlarmService_onClicked(const bool monCheckBox, const bool tueCheckBox, const bool wedCheckBox, const bool thuCheckBox, const bool friCheckBox, const bool satCheckBox, const bool sunCheckBox, const int timeHHSpinBox, const int timeMMSpinBox);


signals:

public slots:

};

#endif // MPDCONFIG_H
