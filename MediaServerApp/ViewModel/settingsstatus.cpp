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

    if (builder.waitForFinished())
    {
        QString info = builder.readAll();
        obj->setProperty("text",QVariant(info));
    }
}

void Settings::checkSystemdStatus(QObject *statusSwitch, QObject *statusButton, const QString nameService)
{
    auto serviceIsEnable = checkSystemdStatusIsEnabled(nameService);
    statusSwitch->setProperty("checked",QVariant(serviceIsEnable));
    statusButton->setProperty("enabled",QVariant(serviceIsEnable));
    if(serviceIsEnable)
    {
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

void Settings::tvHeadEndStatusSwitch_OnClicked(const bool tvHeadEndStatusSwitchIsChecked, QObject *tvHeadEndStatusButton)
{
    StatusSwitch_onClicked(tvHeadEndStatusSwitchIsChecked,tvHeadEndStatusButton,"tvheadend");
}

void Settings::tvHeadEndStatusButton_OnClicked(QObject *tvHeadEndStatusButton, const QString tvHeadEndStatusButtonText)
{
    StatusButton_onClicked(tvHeadEndStatusButton,tvHeadEndStatusButtonText,"tvheadend");
}

void Settings::ympdStatusSwitch_OnClicked(const bool ympdStatusSwitchIsChecked, QObject *ympdStatusButton)
{
    StatusSwitch_onClicked(ympdStatusSwitchIsChecked,ympdStatusButton,"ympd");
}

void Settings::ympdStatusButton_OnClicked(QObject *ympdStatusButton, const QString ympdStatusButtonText)
{
    StatusButton_onClicked(ympdStatusButton, ympdStatusButtonText,"ympd");
}

void Settings::mpdStatusSwitch_OnClicked(const bool mpdStatusSwitchIsChecked, QObject *mpdStatusButton)
{
    StatusSwitch_onClicked(mpdStatusSwitchIsChecked,mpdStatusButton,"mpd");
}

void Settings::mpdStatusButton_OnClicked(QObject *mpdStatusButton, const QString mpdStatusButtonText)
{
    StatusButton_onClicked(mpdStatusButton, mpdStatusButtonText,"mpd");
}

void Settings::dlnaStatusSwitch_OnClicked(const bool dlnaStatusSwitchIsChecked, QObject *dlnaStatusButton)
{
    StatusSwitch_onClicked(dlnaStatusSwitchIsChecked, dlnaStatusButton,"minidlnad");
}

void Settings::dlnaStatusButton_OnClicked(QObject *dlnaStatusButton, const QString dlnaStatusButtonText)
{
    StatusButton_onClicked(dlnaStatusButton, dlnaStatusButtonText,"minidlnad");
}

void Settings::sambaStatusSwitch_OnClicked(const bool sambaStatusSwitchIsChecked, QObject *sambaStatusButton)
{
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, sambaStatusButton,"smb");
    StatusSwitch_onClicked(sambaStatusSwitchIsChecked, sambaStatusButton,"nmb");
}

void Settings::sambaStatusButton_OnClicked(QObject *sambaStatusButton, const QString sambaStatusButtonText)
{
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText,"smb");
    StatusButton_onClicked(sambaStatusButton, sambaStatusButtonText,"nmb");
}

void Settings::ftpStatusSwitch_OnClicked(const bool ftpStatusSwitchIsChecked, QObject *ftpStatusButton)
{
    StatusSwitch_onClicked(ftpStatusSwitchIsChecked, ftpStatusButton,"vsftpd");
}

void Settings::ftpStatusButton_OnClicked(QObject *ftpStatusButton, const QString ftpStatusButtonText)
{
    StatusButton_onClicked(ftpStatusButton, ftpStatusButtonText,"vsftpd");
}

bool Settings::checkSystemdStatusIsActive(const QString &serviceName)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active "+serviceName);
    process.setReadChannel(QProcess::StandardOutput);
    QStringList devicesList;
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
    QStringList devicesList;
    process.waitForFinished();
    auto text = process.readAll();
    return text.contains("enabled");

}

void Settings::StatusSwitch_onClicked(const bool statusSwitchIsChecked, QObject *statusButton, const QString &serviceName)
{
    if(statusSwitchIsChecked)
    {
        QProcess::execute("systemctl enable "+serviceName);
        statusButton->setProperty("text",QVariant("start"));
        statusButton->setProperty("enabled",QVariant(true));
    }
    else
    {
        QProcess::execute("systemctl stop "+serviceName);
        QProcess::execute("systemctl disable "+serviceName);
        statusButton->setProperty("enabled",QVariant(false));
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
