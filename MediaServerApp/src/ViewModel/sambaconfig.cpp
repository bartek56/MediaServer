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

    auto countShare = settings.childGroups().count();

    globalConfig.browseable = settings.value("GLOBAL/browseable").toString();
    globalConfig.domainMaster = settings.value("GLOBAL/domain master").toString();
    globalConfig.forceUser = settings.value("GLOBAL/force user").toString();
    globalConfig.localMaster = settings.value("GLOBAL/local master").toString();
    globalConfig.mapToGuest = settings.value("GLOBAL/map to guest").toString();
    globalConfig.netbiosName = settings.value("GLOBAL/netbios name").toString();
    globalConfig.security = settings.value("GLOBAL/security").toString();
    globalConfig.serverString = settings.value("GLOBAL/server string").toString();
    globalConfig.workgroup = settings.value("GLOBAL/workgroup").toString();

    localConfig.browseable = settings.value("share/browseable").toString();
    localConfig.comment = settings.value("share/comment").toString();
    localConfig.createMode = settings.value("share/create mode").toString();
    localConfig.directoryMode = settings.value("share/directory mode").toString();
    localConfig.guestOk = settings.value("share/guest ok").toString();
    localConfig.path = settings.value("share/path").toString();
    localConfig.readOnly = settings.value("share/read only").toString();
    localConfig.writable = settings.value("share/writable").toString();


    showGlobalConfigs();
    showLocalConfigs();
    if(countShare == 2)
    {
        saveDefaultConfigsForExternalDisk1();
        saveDefaultConfigsForExternalDisk2();
        saveDefaultConfigsForExternalDisk3();
    }
    else if(countShare == 3)
    {
        enabledCheckBox1->setProperty("checked", QVariant(true));

        loadConfigsForExternalDisk1(settings);
        saveDefaultConfigsForExternalDisk2();
        saveDefaultConfigsForExternalDisk3();
    }
    else if(countShare == 4)
    {
        enabledCheckBox1->setProperty("checked", QVariant(true));
        enabledCheckBox2->setProperty("checked", QVariant(true));

        loadConfigsForExternalDisk1(settings);
        loadConfigsForExternalDisk2(settings);
        saveDefaultConfigsForExternalDisk3();
    }
    else if(countShare == 5)
    {
        enabledCheckBox1->setProperty("checked", QVariant(true));
        enabledCheckBox2->setProperty("checked", QVariant(true));
        enabledCheckBox3->setProperty("checked", QVariant(true));

        loadConfigsForExternalDisk1(settings);
        loadConfigsForExternalDisk2(settings);
        loadConfigsForExternalDisk3(settings);
    }

    showConfigsForExternalDisk1();
    showConfigsForExternalDisk2();
    showConfigsForExternalDisk3();
}

void SambaConfig::showLocalConfigs()
{

    nameTextField->setProperty("text", QVariant(localConfig.comment));
    pathTextField->setProperty("text", QVariant(localConfig.path));
    createModeTextField->setProperty("text", QVariant(localConfig.createMode));
    directoryModeTextField->setProperty("text", QVariant(localConfig.directoryMode));

    setCheckboxesFromFileSettings(localConfig.browseable, browsableCheckBox);
    setCheckboxesFromFileSettings(localConfig.writable, writablecheckBox);
    setCheckboxesFromFileSettings(localConfig.guestOk, guestOkCheckBox);
}

void SambaConfig::loadConfigsForExternalDisk1(const QSettings &settings)
{
    shareConfig1.browseable = settings.value("share1/browseable").toString();
    shareConfig1.comment = settings.value("share1/comment").toString();
    shareConfig1.createMode = settings.value("share1/create mode").toString();
    shareConfig1.directoryMode = settings.value("share1/directory mode").toString();
    shareConfig1.guestOk = settings.value("share1/guest ok").toString();
    shareConfig1.path = settings.value("share1/path").toString();
    shareConfig1.readOnly = settings.value("share1/read only").toString();
    shareConfig1.writable = settings.value("share1/writable").toString();
}

void SambaConfig::loadConfigsForExternalDisk2(const QSettings &settings)
{
    shareConfig2.browseable = settings.value("share2/browseable").toString();
    shareConfig2.comment = settings.value("share2/comment").toString();
    shareConfig2.createMode = settings.value("share2/create mode").toString();
    shareConfig2.directoryMode = settings.value("share2/directory mode").toString();
    shareConfig2.guestOk = settings.value("share2/guest ok").toString();
    shareConfig2.path = settings.value("share2/path").toString();
    shareConfig2.readOnly = settings.value("share2/read only").toString();
    shareConfig2.writable = settings.value("share2/writable").toString();
}

void SambaConfig::loadConfigsForExternalDisk3(const QSettings &settings)
{
    shareConfig3.browseable = settings.value("share3/browseable").toString();
    shareConfig3.comment = settings.value("share3/comment").toString();
    shareConfig3.createMode = settings.value("share3/create mode").toString();
    shareConfig3.directoryMode = settings.value("share3/directory mode").toString();
    shareConfig3.guestOk = settings.value("share3/guest ok").toString();
    shareConfig3.path = settings.value("share3/path").toString();
    shareConfig3.readOnly = settings.value("share3/read only").toString();
    shareConfig3.writable = settings.value("share3/writable").toString();
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

void SambaConfig::saveDefaultConfigsForExternalDisk1()
{
    shareConfig1.path = "/mnt/externalDisk1";
    shareConfig1.comment = "DISK1";
    shareConfig1.browseable = "yes";
    shareConfig1.writable = "yes";
    shareConfig1.guestOk = "yes";
    shareConfig1.readOnly = "no";
    shareConfig1.createMode = "0644";
    shareConfig1.directoryMode = "0755";
}

void SambaConfig::saveDefaultConfigsForExternalDisk2()
{
    shareConfig2.path = "/mnt/externalDisk2";
    shareConfig2.comment = "DISK2";
    shareConfig2.browseable = "yes";
    shareConfig2.writable = "yes";
    shareConfig2.guestOk = "yes";
    shareConfig2.readOnly = "no";
    shareConfig2.createMode = "0644";
    shareConfig2.directoryMode = "0755";
}

void SambaConfig::saveDefaultConfigsForExternalDisk3()
{
    shareConfig3.path = "/mnt/externalDisk3";
    shareConfig3.comment = "DISK3";
    shareConfig3.browseable = "yes";
    shareConfig3.writable = "yes";
    shareConfig3.guestOk = "yes";
    shareConfig3.readOnly = "no";
    shareConfig3.createMode = "0644";
    shareConfig3.directoryMode = "0755";
}

void SambaConfig::showConfigsForExternalDisk1()
{
    externalDiskTabButton1->setProperty("visible", QVariant(true));

    createModeTextField1->setProperty("text", QVariant(shareConfig1.createMode));
    directoryModeTextField1->setProperty("text", QVariant(shareConfig1.directoryMode));
    pathTextField1->setProperty("text", QVariant(shareConfig1.path));
    nameTextField1->setProperty("text", QVariant(shareConfig1.comment));
    setCheckboxesFromFileSettings(shareConfig1.browseable, browsableCheckBox1);
    setCheckboxesFromFileSettings(shareConfig1.writable, writablecheckBox1);
    setCheckboxesFromFileSettings(shareConfig1.guestOk, guestOkCheckBox1);
    setCheckboxesFromFileSettings(shareConfig1.readOnly, readOnlyCheckBox1);
}

void SambaConfig::showConfigsForExternalDisk2()
{
    externalDiskTabButton2->setProperty("visible", QVariant(true));
    createModeTextField2->setProperty("text", QVariant(shareConfig2.createMode));
    pathTextField2->setProperty("text", QVariant(shareConfig2.path));
    nameTextField2->setProperty("text", QVariant(shareConfig2.comment));
    directoryModeTextField2->setProperty("text", QVariant(shareConfig2.directoryMode));
    setCheckboxesFromFileSettings(shareConfig2.browseable, browsableCheckBox2);
    setCheckboxesFromFileSettings(shareConfig2.writable, writablecheckBox2);
    setCheckboxesFromFileSettings(shareConfig2.guestOk, guestOkCheckBox2);
    setCheckboxesFromFileSettings(shareConfig2.readOnly, readOnlyCheckBox2);
}

void SambaConfig::showConfigsForExternalDisk3()
{
    externalDiskTabButton3->setProperty("visible", QVariant(true));
    createModeTextField3->setProperty("text", QVariant(shareConfig3.createMode));
    directoryModeTextField3->setProperty("text", QVariant(shareConfig3.directoryMode));
    pathTextField3->setProperty("text", QVariant(shareConfig3.path));
    nameTextField3->setProperty("text", QVariant(shareConfig3.comment));
    setCheckboxesFromFileSettings(shareConfig3.browseable, browsableCheckBox3);
    setCheckboxesFromFileSettings(shareConfig3.writable, writablecheckBox3);
    setCheckboxesFromFileSettings(shareConfig3.guestOk, guestOkCheckBox3);
    setCheckboxesFromFileSettings(shareConfig3.readOnly, readOnlyCheckBox3);
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

    settings.setValue("share/comment", localConfig.comment);
    settings.setValue("share/path", localConfig.path);
    settings.setValue("share/create mode", localConfig.createMode);
    settings.setValue("share/directory mode", localConfig.directoryMode);
    settings.setValue("share/browseable", localConfig.browseable);
    settings.setValue("share/writable", localConfig.writable);
    settings.setValue("share/guest ok", localConfig.guestOk);
    settings.setValue("share/read only", localConfig.readOnly);

    if(enabledCheckBox1->property("checked").toBool())
    {
        settings.setValue("share1/comment", shareConfig1.comment);
        settings.setValue("share1/path", shareConfig1.path);
        settings.setValue("share1/create mode", shareConfig1.createMode);
        settings.setValue("share1/directory mode", shareConfig1.directoryMode);
        settings.setValue("share1/browseable", shareConfig1.browseable);
        settings.setValue("share1/writable", shareConfig1.writable);
        settings.setValue("share1/guest ok", shareConfig1.guestOk);
        settings.setValue("share1/read only", shareConfig1.readOnly);
    }
    if(enabledCheckBox2->property("checked").toBool())
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

    if(enabledCheckBox3->property("checked").toBool())
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

    if(isServiceActive())
    {
        Systemd::restartUnit(Systemd::System, "nmb.service", Systemd::Unit::Replace);
        Systemd::restartUnit(Systemd::System, "smb.service", Systemd::Unit::Replace);
    }
}

void SambaConfig::setSettingFromCheckboxes(QString &configName, bool checked)
{
    if(checked)
    {
        configName = "yes";
    }
    else
    {
        configName = "no";
    }
}

void SambaConfig::setCheckboxesFromFileSettings(const QString configsParameters, QObject *checkbox)
{
    if(!configsParameters.compare("yes"))
    {
        checkbox->setProperty("checked", QVariant(true));
    }
    else
    {
        checkbox->setProperty("checked", QVariant(false));
    }
}

void SambaConfig::setExternalDiskTabButton1(QObject *obj)
{
    externalDiskTabButton1 = obj;
}

void SambaConfig::setExternalDiskTabButton2(QObject *obj)
{
    externalDiskTabButton2 = obj;
}

void SambaConfig::setExternalDiskTabButton3(QObject *obj)
{
    externalDiskTabButton3 = obj;
}

void SambaConfig::bFileDialog_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    pathTextField->setProperty("text", QVariant(path));
    localConfig.path = path;
}

void SambaConfig::bFileDialog1_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    pathTextField1->setProperty("text", QVariant(path));
    shareConfig1.path = path;
}

void SambaConfig::bFileDialog2_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    pathTextField2->setProperty("text", QVariant(path));
    shareConfig2.path = path;
}

void SambaConfig::bFileDialog3_onAccepted(QString catalog)
{
    QString path = catalog.remove(0, 7);
    pathTextField3->setProperty("text", QVariant(path));
    shareConfig3.path = path;
}
