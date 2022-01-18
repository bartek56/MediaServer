#include "sambaconfig.h"

#include <QDebug>
#include <QObject>
#include <QFile>
#include <QtSystemd/sdmanager.h>
#include <QtSystemd/unit.h>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{
}

bool SambaConfig::isServiceActive()
{
    auto unitExist = Systemd::getUnit(Systemd::System, NMB_SERVICE);
    if(unitExist)
    {
        auto text = Systemd::getUnit(Systemd::System, NMB_SERVICE).data()->activeState();
        return !text.contains("in");
    }
    else
    {
        return false;
    }
}


void SambaConfig::loadAllConfigs()
{
    QSettings settings(SAMBA_CONFIG_FILE, QSettings::IniFormat);

    auto keys = settings.childGroups();
    auto countShare = keys.count();

    globalConfig.browseable = settings.value(globalConfigName.BROWSE_ABLE).toString();
    globalConfig.domainMaster = settings.value(globalConfigName.DOMAIN_MASTER).toString();
    globalConfig.forceUser = settings.value(globalConfigName.FORCE_USER).toString();
    globalConfig.localMaster = settings.value(globalConfigName.LOCAL_MASTER).toString();
    globalConfig.mapToGuest = settings.value(globalConfigName.MAP_TO_GUEST).toString();
    globalConfig.netbiosName = settings.value(globalConfigName.NETBIOS_NAME).toString();
    globalConfig.security = settings.value(globalConfigName.SECURITY).toString();
    globalConfig.serverString = settings.value(globalConfigName.SERVER_STRING).toString();
    globalConfig.workgroup = settings.value(globalConfigName.WORKGROUP).toString();

    loadConfigsForShare(shareConfig1, settings, keys.at(1));

    showGlobalConfigs();
    showLocalConfigs();

    if(countShare == 2)
    {
        setDefaultConfigsForShare(shareConfig2, "share2", "/mnt/share2");
        setDefaultConfigsForShare(shareConfig3, "share3", "/mnt/share3");
        setDefaultConfigsForShare(shareConfig4, "share4", "/mnt/share4");
    }
    else if(countShare == 3)
    {
        auto shareName = keys.at(2);
        sambaShare2.enabledCheckBox->setProperty("checked", QVariant(true));
        loadConfigsForShare(shareConfig2, settings, shareName);
        setDefaultConfigsForShare(shareConfig3, "share3", "/mnt/share3");
        setDefaultConfigsForShare(shareConfig4, "share4", "/mnt/share4");
    }
    else if(countShare == 4)
    {
        auto shareName2 = keys.at(2);
        auto shareName3 = keys.at(3);
        sambaShare2.enabledCheckBox->setProperty("checked", QVariant(true));
        sambaShare3.enabledCheckBox->setProperty("checked", QVariant(true));

        loadConfigsForShare(shareConfig2, settings, shareName2);
        loadConfigsForShare(shareConfig3, settings, shareName3);
        setDefaultConfigsForShare(shareConfig4, "share4", "/mnt/share4");
    }
    else if(countShare == 5)
    {
        auto shareName2 = keys.at(2);
        auto shareName3 = keys.at(3);
        auto shareName4 = keys.at(4);
        sambaShare2.enabledCheckBox->setProperty("checked", QVariant(true));
        sambaShare3.enabledCheckBox->setProperty("checked", QVariant(true));
        sambaShare4.enabledCheckBox->setProperty("checked", QVariant(true));

        loadConfigsForShare(shareConfig2, settings, shareName2);
        loadConfigsForShare(shareConfig3, settings, shareName3);
        loadConfigsForShare(shareConfig4, settings, shareName4);
    }

    showConfigsForExternalDisk(sambaShare2, shareConfig2);
    showConfigsForExternalDisk(sambaShare3, shareConfig3);
    showConfigsForExternalDisk(sambaShare4, shareConfig4);
}

void SambaConfig::showLocalConfigs()
{

    sambaShare1.nameTextField->setProperty("text", QVariant(shareConfig1.comment));
    sambaShare1.pathTextField->setProperty("text", QVariant(shareConfig1.path));
    sambaShare1.createModeTextField->setProperty("text", QVariant(shareConfig1.createMode));
    sambaShare1.directoryModeTextField->setProperty("text", QVariant(shareConfig1.directoryMode));

    setCheckboxesFromFileSettings(shareConfig1.browseable, sambaShare1.browsableCheckBox);
    setCheckboxesFromFileSettings(shareConfig1.writable, sambaShare1.writablecheckBox);
    setCheckboxesFromFileSettings(shareConfig1.guestOk, sambaShare1.guestOkCheckBox);
}

void SambaConfig::loadConfigsForShare(ShareConfig &shareConfig, const QSettings &settings, const QString &shareName)
{
    shareConfig.browseable = settings.value(shareName + "/" + configName.BROWSEABLE).toString();
    shareConfig.comment = settings.value(shareName + "/" + configName.COMMENT).toString();
    shareConfig.createMode = settings.value(shareName + "/" + configName.CREATE_MODE).toString();
    shareConfig.directoryMode = settings.value(shareName + "/" + configName.DIRECTORY_MODE).toString();
    shareConfig.guestOk = settings.value(shareName + "/" + configName.GUEST_OK).toString();
    shareConfig.path = settings.value(shareName + "/" + configName.PATH).toString();
    shareConfig.readOnly = settings.value(shareName + "/" + configName.READ_ONLY).toString();
    shareConfig.writable = settings.value(shareName + "/" + configName.WRITABLE).toString();
}

void SambaConfig::setDefaultConfigsForShare(ShareConfig &shareConfig, const QString &name, const QString &path)
{
    shareConfig.path = path;
    shareConfig.comment = name;
    shareConfig.browseable = "yes";
    shareConfig.writable = "yes";
    shareConfig.guestOk = "yes";
    shareConfig.readOnly = "no";
    shareConfig.createMode = "0644";
    shareConfig.directoryMode = "0755";
}

void SambaConfig::showGlobalConfigs()
{
    workGroupTextField->setProperty("text", QVariant(globalConfig.workgroup));
    serverStringTextField->setProperty("text", QVariant(globalConfig.serverString));
    netBiosTextField->setProperty("text", QVariant(globalConfig.netbiosName));

    setCheckboxesFromFileSettings(globalConfig.browseable, globalBrowsableCheckBox);
    setCheckboxesFromFileSettings(globalConfig.localMaster, localMastercheckBox);
    setCheckboxesFromFileSettings(globalConfig.domainMaster, domainMasterCheckBox);
}

void SambaConfig::showConfigsForExternalDisk(const SambaShareObjects &sambaConfig, const ShareConfig &shareConfig)
{
    sambaConfig.createModeTextField->setProperty("text", QVariant(shareConfig.createMode));
    sambaConfig.directoryModeTextField->setProperty("text", QVariant(shareConfig.directoryMode));
    sambaConfig.pathTextField->setProperty("text", QVariant(shareConfig.path));
    sambaConfig.nameTextField->setProperty("text", QVariant(shareConfig.comment));
    setCheckboxesFromFileSettings(shareConfig.browseable, sambaConfig.browsableCheckBox);
    setCheckboxesFromFileSettings(shareConfig.writable, sambaConfig.writablecheckBox);
    setCheckboxesFromFileSettings(shareConfig.guestOk, sambaConfig.guestOkCheckBox);
    setCheckboxesFromFileSettings(shareConfig.readOnly, sambaConfig.readOnlyCheckBox);
}

void SambaConfig::bSave_onClicked()
{
    QSettings settings(SAMBA_CONFIG_FILE, QSettings::IniFormat);

    settings.clear();
    settings.setValue(globalConfigName.WORKGROUP, globalConfig.workgroup);
    settings.setValue(globalConfigName.SERVER_STRING, globalConfig.serverString);
    settings.setValue(globalConfigName.NETBIOS_NAME, globalConfig.netbiosName);
    settings.setValue(globalConfigName.MAP_TO_GUEST, globalConfig.mapToGuest);
    settings.setValue(globalConfigName.FORCE_USER, globalConfig.forceUser);
    settings.setValue(globalConfigName.BROWSE_ABLE, globalConfig.browseable);
    settings.setValue(globalConfigName.LOCAL_MASTER, globalConfig.localMaster);
    settings.setValue(globalConfigName.DOMAIN_MASTER, globalConfig.domainMaster);

    saveShare(settings, shareConfig1);

    if(sambaShare2.enabledCheckBox->property("checked").toBool())
        saveShare(settings, shareConfig2);

    if(sambaShare3.enabledCheckBox->property("checked").toBool())
        saveShare(settings, shareConfig3);

    if(sambaShare4.enabledCheckBox->property("checked").toBool())
        saveShare(settings, shareConfig4);

    if(isServiceActive())
    {
        Systemd::restartUnit(Systemd::System, NMB_SERVICE, Systemd::Unit::Replace);
        Systemd::restartUnit(Systemd::System, SMB_SERVICE, Systemd::Unit::Replace);
    }
    settings.sync();

    QProcess::startDetached("/bin/bash", QStringList() << "-c"
                                                       << "sed -i 's/%20/ /g' " + SAMBA_CONFIG_FILE + " ");
}


void SambaConfig::saveShare(QSettings &settings, const ShareConfig &shareConfig)
{
    settings.setValue(shareConfig.comment + "/" + configName.COMMENT, shareConfig.comment);
    settings.setValue(shareConfig.comment + "/" + configName.PATH, shareConfig.path);
    settings.setValue(shareConfig.comment + "/" + configName.CREATE_MODE, shareConfig.createMode);
    settings.setValue(shareConfig.comment + "/" + configName.DIRECTORY_MODE, shareConfig.directoryMode);
    settings.setValue(shareConfig.comment + "/" + configName.BROWSEABLE, shareConfig.browseable);
    settings.setValue(shareConfig.comment + "/" + configName.WRITABLE, shareConfig.writable);
    settings.setValue(shareConfig.comment + "/" + configName.GUEST_OK, shareConfig.guestOk);
    settings.setValue(shareConfig.comment + "/" + configName.READ_ONLY, shareConfig.readOnly);
}


void SambaConfig::setSettingFromCheckboxes(QString &configName, bool checked)
{
    if(checked)
        configName = "yes";
    else
        configName = "no";
}

void SambaConfig::setCheckboxesFromFileSettings(const QString configsParameters, QObject *checkbox)
{
    if(!configsParameters.compare("yes"))
        checkbox->setProperty("checked", QVariant(true));
    else
        checkbox->setProperty("checked", QVariant(false));
}

void SambaConfig::bFileDialog_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    sambaShare1.pathTextField->setProperty("text", QVariant(path));
    shareConfig1.path = path;
}

void SambaConfig::bFileDialog1_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    sambaShare2.pathTextField->setProperty("text", QVariant(path));
    shareConfig2.path = path;
}

void SambaConfig::bFileDialog2_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    sambaShare3.pathTextField->setProperty("text", QVariant(path));
    shareConfig3.path = path;
}

void SambaConfig::bFileDialog3_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    sambaShare4.pathTextField->setProperty("text", QVariant(path));
    shareConfig4.path = path;
}
