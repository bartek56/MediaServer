#include "sambaconfig.h"



void SambaConfig::tfName3_onEditingFinished(QString text)
{
    vConfigs[4].name="["+text+"]";
}
void SambaConfig::tfPath3_onEditingFinished(QString text)
{
    vConfigs[4].configs.at(configName.PATH)=text;
}

void SambaConfig::tfCreateMode3_onEditingFinished(QString text)
{
    vConfigs[4].configs.at(configName.CREATE_MODE)=text;
}

void SambaConfig::tfDirectoryMode3_onEditingFinished(QString text)
{
    vConfigs[4].configs.at(configName.DIRECTORY_MODE)=text;
}

void SambaConfig::chbBrowseable3_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.BROWSEABLE,checked);
}

void SambaConfig::chbWritable3_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.WRITABLE,checked);
}

void SambaConfig::chbGuestOk3_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.GUEST_OK,checked);
}

void SambaConfig::chbReadOnly3_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.READ_ONLY,checked);
}

void SambaConfig::setCommentTextField3(QObject* obj)
{
    nameTextField3 = obj;
}

void SambaConfig::setPathTextField3(QObject* obj)
{
    pathTextField3 = obj;
}

void SambaConfig::setCreateModeTextField3(QObject* obj)
{
    createModeTextField3 = obj;
}

void SambaConfig::setDirectoryModeTextField3(QObject* obj)
{
    directoryModeTextField3 = obj;
}

void SambaConfig::setBrowsableCheckBox3(QObject* obj)
{
    browsableCheckBox3 = obj;
}

void SambaConfig::setWritablecheckBox3(QObject* obj)
{
    writablecheckBox3 = obj;
}

void SambaConfig::setGuestOkCheckBox3(QObject* obj)
{
    guestOkCheckBox3 = obj;
}

void SambaConfig::setReadOnlyCheckBox3(QObject* obj)
{
    readOnlyCheckBox3 = obj;
}

void SambaConfig::setEnabled3(QObject* obj)
{
    enabledCheckBox3 = obj;
}

