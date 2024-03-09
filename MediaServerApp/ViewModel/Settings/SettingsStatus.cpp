#include "SettingsStatus.h"

#include <QtSystemd/sdmanager.h>
#include <QtSystemd/unit.h>
#include <QProcess>

SettingsStatus::SettingsStatus(QObject *parent) : QObject(parent)
{
    ///TODO QDBusAbstractInterface: type UnitConditionList must be registered with Qt D-Bus before it can be used to read property
    Systemd::getUnit(Systemd::System, MPD_SERVICE);
}

void SettingsStatus::checkTvHeadEndServiceStatus(QObject *statusSwitch, QObject *statusButton)
{
    checkSystemdStatus(statusSwitch, statusButton, TVHEADEND_SERVICE);
}

void SettingsStatus::tvHeadEndStatusSwitch_OnClicked(const bool tvHeadEndStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(tvHeadEndStatusSwitchIsChecked, TVHEADEND_SERVICE);
}

void SettingsStatus::tvHeadEndStatusButton_OnClicked(QObject *tvHeadEndStatusSwitch, const QString tvHeadEndStatusButton)
{
    StatusButton_onClicked(tvHeadEndStatusSwitch, tvHeadEndStatusButton, TVHEADEND_SERVICE);
}

void SettingsStatus::checkYMPDSystemdStatus(QObject *ympdStatusSwitch, QObject *ympdStatusButton)
{
    checkSystemdStatus(ympdStatusSwitch, ympdStatusButton, YMPD_SERVICE);
}

void SettingsStatus::ympdStatusSwitch_OnClicked(const bool ympdStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(ympdStatusSwitchIsChecked, YMPD_SERVICE);
}

void SettingsStatus::ympdStatusButton_OnClicked(QObject *ympdStatusSwitch, const QString ympdStatusButton)
{
    StatusButton_onClicked(ympdStatusSwitch, ympdStatusButton, YMPD_SERVICE);
}

void SettingsStatus::checkMPDSystemdStatus(QObject *mpdStatusSwitch, QObject *mpdStatusButton)
{
    checkSystemdStatus(mpdStatusSwitch, mpdStatusButton, MPD_SERVICE);
}

void SettingsStatus::mpdStatusSwitch_OnClicked(const bool mpdStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(mpdStatusSwitchIsChecked, MPD_SERVICE);
}

void SettingsStatus::mpdStatusButton_OnClicked(QObject *mpdStatusButton, const QString mpdStatusButtonText)
{
    StatusButton_onClicked(mpdStatusButton, mpdStatusButtonText, MPD_SERVICE);
}

void SettingsStatus::checkDLNASystemdStatus(QObject *dlnaStatusSwitch, QObject *dlnaStatusButton)
{
    checkSystemdStatus(dlnaStatusSwitch, dlnaStatusButton, MINIDLNA_SERVICE);
}

void SettingsStatus::dlnaStatusSwitch_OnClicked(const bool dlnaStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(dlnaStatusSwitchIsChecked, MINIDLNA_SERVICE);
}

void SettingsStatus::dlnaStatusButton_OnClicked(QObject *dlnaStatusButton, const QString dlnaStatusButtonText)
{
    StatusButton_onClicked(dlnaStatusButton, dlnaStatusButtonText, MINIDLNA_SERVICE);
}

void SettingsStatus::checkSMBSystemdStatus(QObject *smbStatusSwitch, QObject *smbStatusButton)
{
    checkSystemdStatus(smbStatusSwitch, smbStatusButton, SMB_SERVICE);
}

void SettingsStatus::sambaStatusSwitch_OnClicked(const bool sambaStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, SMB_SERVICE);
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, NMB_SERVICE);
}

void SettingsStatus::sambaStatusButton_OnClicked(QObject *sambaStatusButton, const QString sambaStatusButtonText)
{
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText, SMB_SERVICE);
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText, NMB_SERVICE);
}

void SettingsStatus::checkFTPSystemdStatus(QObject *ftpStatusSwitch, QObject *ftpStatusButton)
{
    checkSystemdStatus(ftpStatusSwitch, ftpStatusButton, VSFTPD_SERVICE);
}

void SettingsStatus::ftpStatusSwitch_OnClicked(const bool ftpStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(ftpStatusSwitchIsChecked, VSFTPD_SERVICE);
}

void SettingsStatus::ftpStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText)
{
    StatusButton_onClicked(ftpStatusButton, ftpStatusButtonText, VSFTPD_SERVICE);
}

void SettingsStatus::checkFileBrowserSystemdStatus(QObject *fileBrowserStatusSwitch, QObject *fileBrowserStatusButton)
{
    checkSystemdStatus(fileBrowserStatusSwitch, fileBrowserStatusButton, FILEBROWSER_SERVICE);
}

void SettingsStatus::fileBrowserStatusSwitch_OnClicked(const bool fileBrowserStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(fileBrowserStatusSwitchIsChecked, FILEBROWSER_SERVICE);
}

void SettingsStatus::fileBrowserStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText)
{
    StatusButton_onClicked(ftpStatusButton, ftpStatusButtonText, FILEBROWSER_SERVICE);
}

void SettingsStatus::checkTorrentClientSystemdStatus(QObject *torrentClientStatusSwitch, QObject *torrentCLientStatusButton)
{
    checkSystemdStatus(torrentClientStatusSwitch, torrentCLientStatusButton, TRANSMISSION_SERVICE);
}

void SettingsStatus::torrentClientStatusSwitch_OnClicked(const bool torrentClientStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(torrentClientStatusSwitchIsChecked, TRANSMISSION_SERVICE);
}

void SettingsStatus::torrentClientStatusButton_OnClicked(QObject *torrentClientStatusButton, const QString torrentClientStatusButtonText)
{
    StatusButton_onClicked(torrentClientStatusButton, torrentClientStatusButtonText, TRANSMISSION_SERVICE);
}

bool SettingsStatus::checkSystemdStatusIsActive(const QString &serviceName)
{
    auto text = Systemd::loadUnit(Systemd::System, serviceName)->activeState();
    return !text.contains("in");
}

bool SettingsStatus::checkSystemdStatusIsEnabled(const QString &serviceName)
{
    auto state = Systemd::getUnitFileState(Systemd::System, serviceName);
    return state.contains("enabled");
}

bool SettingsStatus::checkSystemdStatusExist(const QString &serviceName)
{
    auto state = Systemd::getUnitFileState(Systemd::System, serviceName);
    return state.contains("able");
}

void SettingsStatus::checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString &serviceName)
{
    auto serviceExist = false;
    auto state = Systemd::getUnitFileState(Systemd::System, serviceName);

    if(state.contains("able"))
        serviceExist = true;

    statusButton->setProperty("enabled", QVariant(serviceExist));
    statusSwitch->setProperty("enabled", QVariant(serviceExist));

    if(serviceExist)
    {
        bool serviceIsEnable = state.contains("enabled");
        statusSwitch->setProperty("checked", QVariant(serviceIsEnable));
        auto serviceIsActive = checkSystemdStatusIsActive(serviceName);

        if(serviceIsActive)
        {
            statusButton->setProperty("text", QVariant("stop"));
        }
        else
        {
            statusButton->setProperty("text", QVariant("start"));
        }
    }
}

void SettingsStatus::StatusSwitch_onClicked(const bool statusSwitchIsChecked, const QString &serviceName)
{
    if(statusSwitchIsChecked)
        Systemd::enableUnitFiles(Systemd::System, QStringList() << serviceName, false, true);
    else
        Systemd::disableUnitFiles(Systemd::System, QStringList() << serviceName, false);
}

void SettingsStatus::StatusButton_onClicked(QObject *statusButton, const QString statusButtonText, const QString &serviceName)
{
    if(statusButtonText.contains("start"))
    {
        Systemd::startUnit(Systemd::System, serviceName, Systemd::Unit::Replace);
        statusButton->setProperty("text", QVariant("stop"));
    }
    else
    {
        Systemd::stopUnit(Systemd::System, serviceName, Systemd::Unit::Replace);
        statusButton->setProperty("text", QVariant("start"));
    }
}

void SettingsStatus::updateNetworkStatus(QObject *obj)
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("networkctl", QStringList() << "status");

    while(builder.waitForFinished())
        ;

    QString resultInfo = "";
    while(builder.canReadLine())
    {
        auto line = builder.readLine();
        if(line.contains("systemd"))
        {
            break;
        }
        resultInfo += line;
    }
    obj->setProperty("text", QVariant(resultInfo));
}
