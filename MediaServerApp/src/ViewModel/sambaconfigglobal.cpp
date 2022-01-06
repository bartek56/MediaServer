#include "sambaconfig.h"

void SambaConfig::tfNetbiosName_onEditingFinished(QString text)
{
    globalConfig.netbiosName = text;
}

void SambaConfig::tfWorkgroup_onEditingFinished(QString text)
{
    globalConfig.workgroup = text;
}

void SambaConfig::tfServerString_onEditingFinished(QString text)
{
    globalConfig.serverString = text;
}

void SambaConfig::cbMapToGuest_onDisplayTextChanged(QString text)
{
    globalConfig.mapToGuest = text;
}

void SambaConfig::cbSecurity_onDisplayTextChanged(QString text)
{
    globalConfig.security = text;
}

void SambaConfig::cbLocalMaster_onClicked(bool checked)
{
    setSettingFromCheckboxes(globalConfig.localMaster, checked);
}

void SambaConfig::cbDomainMaster_onClicked(bool checked)
{
    setSettingFromCheckboxes(globalConfig.domainMaster, checked);
}

void SambaConfig::cbGlobalBrowseable_onClicked(bool checked)
{
    setSettingFromCheckboxes(globalConfig.browseable, checked);
}

void SambaConfig::setWorkGroupTextField(QObject *obj)
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
    stackLayout = obj;
}
