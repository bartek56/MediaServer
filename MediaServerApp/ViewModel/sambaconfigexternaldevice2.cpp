#include "sambaconfig.h"



void SambaConfig::tfName2_onEditingFinished(QString text)
{
    vConfigs[3].name="["+text+"]";
}

void SambaConfig::tfPath2_onEditingFinished(QString text)
{
    vConfigs[3].configs.at(configName.PATH)=text;
}

void SambaConfig::tfCreateMode2_onEditingFinished(QString text)
{
    vConfigs[3].configs.at(configName.CREATE_MODE)=text;
}

void SambaConfig::tfDirectoryMode2_onEditingFinished(QString text)
{
    vConfigs[3].configs.at(configName.DIRECTORY_MODE)=text;
}

void SambaConfig::chbBrowseable2_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.BROWSEABLE,checked);
}

void SambaConfig::chbWritable2_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.WRITABLE,checked);
}

void SambaConfig::chbGuestOk2_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.GUEST_OK,checked);
}

void SambaConfig::chbReadOnly2_onClicked(bool checked)
{
    setSettingFromCheckboxes(3,configName.READ_ONLY,checked);
}

void SambaConfig::setCommentTextField2(QObject* obj)
{
    nameTextField2 = obj;
}

void SambaConfig::setPathTextField2(QObject* obj)
{
    pathTextField2 = obj;
}

void SambaConfig::setCreateModeTextField2(QObject* obj)
{
    createModeTextField2 = obj;
}

void SambaConfig::setDirectoryModeTextField2(QObject* obj)
{
    directoryModeTextField2 = obj;
}

void SambaConfig::setBrowsableCheckBox2(QObject* obj)
{
    browsableCheckBox2 = obj;
}

void SambaConfig::setWritablecheckBox2(QObject* obj)
{
    writablecheckBox2 = obj;
}

void SambaConfig::setGuestOkCheckBox2(QObject* obj)
{
    guestOkCheckBox2 = obj;
}

void SambaConfig::setReadOnlyCheckBox2(QObject* obj)
{
    readOnlyCheckBox2 = obj;
}

void SambaConfig::setEnabled2(QObject* obj)
{
    enabledCheckBox2 = obj;
}

