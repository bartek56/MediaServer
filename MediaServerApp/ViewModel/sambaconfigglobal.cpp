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

void SambaConfig::setGlobalBrowsableCheckBox(QObject *obj)
{
    globalBrowsableCheckBox = QSharedPointer<QObject>(obj);
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
