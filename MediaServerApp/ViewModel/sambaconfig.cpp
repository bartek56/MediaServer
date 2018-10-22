#include "sambaconfig.h"

#include <QDebug>
#include <QProcess>
SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{

}

void SambaConfig::tfNetbiosName_onEditingFinished(QString text)
{
    vConfigs[0].configs.at(configName.NETBIOS_NAME)=text;
}

void SambaConfig::tfWorkgroup_onEditingFinished(QString text)
{
    vConfigs[0].configs.at(configName.WORKGROUP)=text;
}

void SambaConfig::tfServerString_onEditingFinished(QString text)
{
    vConfigs[0].configs.at(configName.SERVER_STRING)=text;
}

void SambaConfig::cbMapToGuest_onDisplayTextChanged(QString text)
{
    if(!vConfigs.empty())
    {
        vConfigs[0].configs.at(configName.MAP_TO_GUEST)=text;
    }

}

void SambaConfig::cbSecurity_onDisplayTextChanged(QString text)
{
    if(!vConfigs.empty())
    {
        vConfigs[0].configs.at(configName.SECURITY)=text;
    }
}

void SambaConfig::cbLocalMaster_onClicked(bool checked)
{
    setSettingFromCheckboxes(configName.LOCAL_MASTER,checked);
}

void SambaConfig::cbDomainMaster_onClicked(bool checked)
{
   setSettingFromCheckboxes(configName.DOMAIN_MASTER, checked);
}

void SambaConfig::cbBrowseable_onClicked(bool checked)
{
    setSettingFromCheckboxes(configName.BROWSEABLE,checked);
}

void SambaConfig::bSave_onClicked()
{
    editFile.SaveFile("/etc/samba/smb.conf", vConfigs);
    QProcess::execute("systemctl restart nmbd");
    QProcess::execute("systemctl restart smbd");
}

void SambaConfig::openFile()
{
    vConfigs = editFile.OpenFile("/etc/samba/smb.conf");
    loadConfigs();
}

void SambaConfig::loadConfigs()
{
    auto globalConfig = vConfigs[0];
    auto configsParameters = globalConfig.configs;

    workGroupTextField->setProperty("text",QVariant(configsParameters.at(configName.WORKGROUP)));
    serverStringTextField->setProperty("text",QVariant(configsParameters.at(configName.SERVER_STRING)));
    netBiosTextField->setProperty("text",QVariant(configsParameters.at(configName.NETBIOS_NAME)));

    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox);
    setCheckboxesFromFileSettings(configsParameters.at(configName.LOCAL_MASTER), localMastercheckBox);
    setCheckboxesFromFileSettings(configsParameters.at(configName.DOMAIN_MASTER), domainMasterCheckBox);
}

void SambaConfig::setSettingFromCheckboxes(QString configName,bool checked)
{
    if(checked)
    {
        vConfigs[0].configs.at(configName) = "yes";
    }
    else
    {
        vConfigs[0].configs.at(configName) = "no";
    }
}

void SambaConfig::setCheckboxesFromFileSettings(const QString configsParameters, QSharedPointer<QObject> checkbox)
{
    if(!configsParameters.compare("yes"))
    {
        checkbox->setProperty("checked",QVariant(true));
    }
    else
    {
        checkbox->setProperty("checked",QVariant(false));
    }
}
void SambaConfig::setWorkGroupTextField(QObject* obj)
{
    workGroupTextField = QSharedPointer<QObject>(obj);
}
void SambaConfig::setServerStringTextField(QObject *obj)
{
    serverStringTextField = QSharedPointer<QObject>(obj);
}
void SambaConfig::setNetBiosTextField(QObject *obj)
{
    netBiosTextField = QSharedPointer<QObject>(obj);
}
void SambaConfig::setBrowsableCheckBox(QObject *obj)
{
    browsableCheckBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setLocalMastercheckBox(QObject *obj)
{
    localMastercheckBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setDomainMasterCheckBox(QObject *obj)
{
    domainMasterCheckBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setSecurityComboBox(QObject *obj)
{
    securityComboBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setMapToGuestComboBox(QObject *obj)
{
    mapToGuestComboBox = QSharedPointer<QObject>(obj);
}

