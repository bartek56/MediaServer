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
    auto unitExist = Systemd::getUnit(Systemd::System, "nmb.service");
    if(unitExist)
    {
        auto text = Systemd::getUnit(Systemd::System, "nmb.service").data()->activeState();
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

    //auto countShare = settings.childGroups().count();
    auto keys = settings.allKeys();

    globalConfig.browseable = settings.value("GLOBAL/browseable").toString();
    globalConfig.domainMaster = settings.value("GLOBAL/domain master").toString();
    globalConfig.forceUser = settings.value("GLOBAL/force user").toString();
    globalConfig.localMaster = settings.value("GLOBAL/local master").toString();
    globalConfig.mapToGuest = settings.value("GLOBAL/map to guest").toString();
    globalConfig.netbiosName = settings.value("GLOBAL/netbios name").toString();
    globalConfig.security = settings.value("GLOBAL/security").toString();
    globalConfig.serverString = settings.value("GLOBAL/server string").toString();
    globalConfig.workgroup = settings.value("GLOBAL/workgroup").toString();

    shareConfig1.browseable = settings.value("share1/browseable").toString();
    shareConfig1.comment = settings.value("share1/comment").toString();
    shareConfig1.createMode = settings.value("share1/create mode").toString();
    shareConfig1.directoryMode = settings.value("share1/directory mode").toString();
    shareConfig1.guestOk = settings.value("share1/guest ok").toString();
    shareConfig1.path = settings.value("share1/path").toString();
    shareConfig1.readOnly = settings.value("share1/read only").toString();
    shareConfig1.writable = settings.value("share1/writable").toString();


    showGlobalConfigs();
    showLocalConfigs();

    if(keys.contains("share2/path"))
    {
        loadConfigsForShare2_4(shareConfig2, settings, "share2");
        sambaShare2.enabledCheckBox->setProperty("checked", QVariant(true));
    }
    else
        setDefaultConfigs(shareConfig2, "share2", "/mnt/share2");


    if(keys.contains("share3/path"))
    {
        loadConfigsForShare2_4(shareConfig3, settings, "share3");
        sambaShare3.enabledCheckBox->setProperty("checked", QVariant(true));
    }
    else
        setDefaultConfigs(shareConfig3, "share3", "/mnt/share3");


    if(keys.contains("share4/path"))
    {
        loadConfigsForShare2_4(shareConfig4, settings, "share4");
        sambaShare4.enabledCheckBox->setProperty("checked", QVariant(true));
    }
    else
        setDefaultConfigs(shareConfig4, "share4", "/mnt/share4");

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

void SambaConfig::loadConfigsForShare2_4(ShareConfig &shareConfig, const QSettings &settings, const QString &shareName)
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

void SambaConfig::setDefaultConfigs(ShareConfig &shareConfig, const QString &name, const QString &path)
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
    settings.setValue("GLOBAL/workgroup", globalConfig.workgroup);
    settings.setValue("GLOBAL/server string", globalConfig.serverString);
    settings.setValue("GLOBAL/netbios name", globalConfig.netbiosName);
    settings.setValue("GLOBAL/map to guest", globalConfig.mapToGuest);
    settings.setValue("GLOBAL/force user", globalConfig.forceUser);
    settings.setValue("GLOBAL/browseable", globalConfig.browseable);
    settings.setValue("GLOBAL/local master", globalConfig.localMaster);
    settings.setValue("GLOBAL/domain master", globalConfig.domainMaster);

    settings.setValue("share1/comment", shareConfig1.comment);
    settings.setValue("share1/path", shareConfig1.path);
    settings.setValue("share1/create mode", shareConfig1.createMode);
    settings.setValue("share1/directory mode", shareConfig1.directoryMode);
    settings.setValue("share1/browseable", shareConfig1.browseable);
    settings.setValue("share1/writable", shareConfig1.writable);
    settings.setValue("share1/guest ok", shareConfig1.guestOk);
    settings.setValue("share1/read only", shareConfig1.readOnly);

    if(sambaShare2.enabledCheckBox->property("checked").toBool())
    {
        settings.setValue("share2/comment", shareConfig2.comment);
        settings.setValue("share2/path", shareConfig2.path);
        settings.setValue("share2/create mode", shareConfig2.createMode);
        settings.setValue("share2/directory mode", shareConfig2.directoryMode);
        settings.setValue("share2/browseable", shareConfig2.browseable);
        settings.setValue("share2/writable", shareConfig2.writable);
        settings.setValue("share2/guest ok", shareConfig2.guestOk);
        settings.setValue("share2/read only", shareConfig2.readOnly);
    }
    if(sambaShare3.enabledCheckBox->property("checked").toBool())
    {
        settings.setValue("share3/comment", shareConfig3.comment);
        settings.setValue("share3/path", shareConfig3.path);
        settings.setValue("share3/create mode", shareConfig3.createMode);
        settings.setValue("share3/directory mode", shareConfig3.directoryMode);
        settings.setValue("share3/browseable", shareConfig3.browseable);
        settings.setValue("share3/writable", shareConfig3.writable);
        settings.setValue("share3/guest ok", shareConfig3.guestOk);
        settings.setValue("share3/read only", shareConfig3.readOnly);
    }

    if(sambaShare4.enabledCheckBox->property("checked").toBool())
    {
        settings.setValue("share4/comment", shareConfig4.comment);
        settings.setValue("share4/path", shareConfig4.path);
        settings.setValue("share4/create mode", shareConfig4.createMode);
        settings.setValue("share4/directory mode", shareConfig4.directoryMode);
        settings.setValue("share4/browseable", shareConfig4.browseable);
        settings.setValue("share4/writable", shareConfig4.writable);
        settings.setValue("share4/guest ok", shareConfig4.guestOk);
        settings.setValue("share4/read only", shareConfig4.readOnly);
    }

    if(isServiceActive())
    {
        Systemd::restartUnit(Systemd::System, "nmb.service", Systemd::Unit::Replace);
        Systemd::restartUnit(Systemd::System, "smb.service", Systemd::Unit::Replace);
    }
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
