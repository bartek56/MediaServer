#include "sambaconfig.h"

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
    setSettingFromCheckboxes(0,configName.LOCAL_MASTER,checked);
}

void SambaConfig::cbDomainMaster_onClicked(bool checked)
{
   setSettingFromCheckboxes(0,configName.DOMAIN_MASTER, checked);
}

void SambaConfig::cbGlobalBrowseable_onClicked(bool checked)
{
    setSettingFromCheckboxes(0,configName.BROWSEABLE,checked);
}

void SambaConfig::setWorkGroupTextField(QObject* obj)
{
    workGroupTextField = obj;
}

void SambaConfig::setServerStringTextField(QObject *obj)
{
    serverStringTextField = obj;
}

void SambaConfig::setNetBiosTextField(QObject *obj)
{
    netBiosTextField = obj;
}

void SambaConfig::setGlobalBrowsableCheckBox(QObject *obj)
{
    globalBrowsableCheckBox = obj;
}

void SambaConfig::setLocalMasterCheckBox(QObject *obj)
{
    localMastercheckBox = obj;
}

void SambaConfig::setDomainMasterCheckBox(QObject *obj)
{
    domainMasterCheckBox = obj;
}

void SambaConfig::setSecurityComboBox(QObject *obj)
{
    securityComboBox = obj;
}

void SambaConfig::setMapToGuestComboBox(QObject *obj)
{
    mapToGuestComboBox = obj;
}

void SambaConfig::setStackLayout(QObject *obj)
{
    stackLayout=obj;
}
