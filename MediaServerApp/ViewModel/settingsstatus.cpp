#include "settings.h"

#include <QDebug>
#include <QFile>
#include <map>

Settings::Settings(QObject *parent) : QObject(parent)
{

}

void Settings::updateNetworkStatus(QObject *obj)
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("networkctl status");

    while(builder.waitForFinished());

    QString info = builder.readAll();
    obj->setProperty("text",QVariant(info));
}

void Settings::checkTvHeadEndServiceStatus(QObject *statusSwitch, QObject *statusButton)
{
    checkSystemdStatus(statusSwitch, statusButton, TVHEADEND_SERVICE);
}

void Settings::tvHeadEndStatusSwitch_OnClicked(const bool tvHeadEndStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(tvHeadEndStatusSwitchIsChecked, TVHEADEND_SERVICE);
}

void Settings::tvHeadEndStatusButton_OnClicked(QObject *tvHeadEndStatusSwitch, const QString tvHeadEndStatusButton)
{
    StatusButton_onClicked(tvHeadEndStatusSwitch, tvHeadEndStatusButton, TVHEADEND_SERVICE);
}


void Settings::checkYMPDSystemdStatus(QObject *ympdStatusSwitch, QObject *ympdStatusButton)
{
    checkSystemdStatus(ympdStatusSwitch, ympdStatusButton, YMPD_SERVICE);
}

void Settings::ympdStatusSwitch_OnClicked(const bool ympdStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(ympdStatusSwitchIsChecked, YMPD_SERVICE);
}

void Settings::ympdStatusButton_OnClicked(QObject *ympdStatusSwitch, const QString ympdStatusButton)
{
    StatusButton_onClicked(ympdStatusSwitch, ympdStatusButton, YMPD_SERVICE);
}



void Settings::checkMPDSystemdStatus(QObject *mpdStatusSwitch, QObject *mpdStatusButton)
{
     checkSystemdStatus(mpdStatusSwitch, mpdStatusButton, MPD_SERVICE);
}

void Settings::mpdStatusSwitch_OnClicked(const bool mpdStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(mpdStatusSwitchIsChecked, MPD_SERVICE);
}

void Settings::mpdStatusButton_OnClicked(QObject *mpdStatusButton, const QString mpdStatusButtonText)
{
    StatusButton_onClicked(mpdStatusButton, mpdStatusButtonText, MPD_SERVICE);
}


void Settings::checkDLNASystemdStatus(QObject *dlnaStatusSwitch, QObject *dlnaStatusButton)
{
    checkSystemdStatus(dlnaStatusSwitch, dlnaStatusButton, MINIDLNA_SERVICE);
}

void Settings::dlnaStatusSwitch_OnClicked(const bool dlnaStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(dlnaStatusSwitchIsChecked, MINIDLNA_SERVICE);
}

void Settings::dlnaStatusButton_OnClicked(QObject *dlnaStatusButton, const QString dlnaStatusButtonText)
{
    StatusButton_onClicked(dlnaStatusButton, dlnaStatusButtonText, MINIDLNA_SERVICE);
}


void Settings::checkSMBSystemdStatus(QObject *smbStatusSwitch, QObject *smbStatusButton)
{
    checkSystemdStatus(smbStatusSwitch, smbStatusButton, SMB_SERVICE);
}

void Settings::sambaStatusSwitch_OnClicked(const bool sambaStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, SMB_SERVICE);
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, NMB_SERVICE);
}

void Settings::sambaStatusButton_OnClicked(QObject *sambaStatusButton, const QString sambaStatusButtonText)
{
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText, SMB_SERVICE);
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText, NMB_SERVICE);
}



void Settings::checkFTPSystemdStatus(QObject *ftpStatusSwitch, QObject *ftpStatusButton)
{
    checkSystemdStatus(ftpStatusSwitch, ftpStatusButton, VSFTPD_SERVICE);
}

void Settings::ftpStatusSwitch_OnClicked(const bool ftpStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(ftpStatusSwitchIsChecked, VSFTPD_SERVICE);
}

void Settings::ftpStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText)
{
    StatusButton_onClicked(ftpStatusButton, ftpStatusButtonText, VSFTPD_SERVICE);
}



void Settings::checkFileBrowserSystemdStatus(QObject *fileBrowserStatusSwitch, QObject *fileBrowserStatusButton)
{
    checkSystemdStatus(fileBrowserStatusSwitch, fileBrowserStatusButton, FILEBROWSER_SERVICE);
}

void Settings::fileBrowserStatusSwitch_OnClicked(const bool fileBrowserStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(fileBrowserStatusSwitchIsChecked, FILEBROWSER_SERVICE);
}

void Settings::fileBrowserStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText)
{
    StatusButton_onClicked(ftpStatusButton, ftpStatusButtonText, FILEBROWSER_SERVICE);
}



void Settings::checkTorrentClientSystemdStatus(QObject *torrentClientStatusSwitch, QObject *torrentCLientStatusButton)
{
    checkSystemdStatus(torrentClientStatusSwitch, torrentCLientStatusButton, TRANSMISSION_SERVICE);
}

void Settings::torrentClientStatusSwitch_OnClicked(const bool torrentClientStatusSwitchIsChecked)
{
    StatusSwitch_onClicked(torrentClientStatusSwitchIsChecked, TRANSMISSION_SERVICE);
}

void Settings::torrentClientStatusButton_OnClicked(QObject *torrentClientStatusButton, const QString torrentClientStatusButtonText)
{
    StatusButton_onClicked(torrentClientStatusButton, torrentClientStatusButtonText, TRANSMISSION_SERVICE);
}

bool Settings::checkSystemdStatusIsActive(const QString &serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active "+serviceName);
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    return !text.contains("in");
}

bool Settings::checkSystemdStatusIsEnabled(const QString &serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-enabled "+serviceName);
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    return text.contains("enabled");
}

bool Settings::checkSystemdStatusExist(const QString &serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-enabled "+serviceName);
    process.setReadChannel(QProcess::StandardOutput);
    process.waitForFinished();
    auto text = process.readAll();
    return (text.contains("enabled") || text.contains("disabled"));
}

void Settings::checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString nameService)
{
    auto serviceExist = checkSystemdStatusExist(nameService);

    statusButton->setProperty("enabled",QVariant(serviceExist));
    statusSwitch->setProperty("enabled",QVariant(serviceExist));

    if(serviceExist)
    {
      bool serviceIsEnable = checkSystemdStatusIsEnabled(nameService);
      statusSwitch->setProperty("checked",QVariant(serviceIsEnable));
      auto serviceIsActive = checkSystemdStatusIsActive(nameService);

      if(serviceIsActive)
      {
          statusButton->setProperty("text",QVariant("stop"));
      }
      else
      {
          statusButton->setProperty("text",QVariant("start"));
      }
    }
}

void Settings::StatusSwitch_onClicked(const bool statusSwitchIsChecked, const QString &serviceName)
{
    if(statusSwitchIsChecked)
    {
        QProcess::execute("systemctl enable "+serviceName);
    }
    else
    {
        QProcess::execute("systemctl disable "+serviceName);
    }
}

void Settings::StatusButton_onClicked(QObject *statusButton, const QString statusButtonText, const QString &serviceName)
{
    if(statusButtonText.contains("start"))
    {
        QProcess::execute("systemctl start " + serviceName);
        statusButton->setProperty("text",QVariant("stop"));
    }
    else
    {
        QProcess::execute("systemctl stop " + serviceName);
        statusButton->setProperty("text",QVariant("start"));
    }
}
