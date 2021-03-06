#include "sambaconfig.h"
#include <QObject>


void SambaConfig::tfName_onEditingFinished(QString text)
{
    vConfigs[1].configs.at(configName.COMMENT)=text;
    vConfigs[1].name="["+text+"]";
}

void SambaConfig::tfCreateMode_onEditingFinished(QString text)
{
    vConfigs[1].configs.at(configName.CREATE_MODE)=text;
}

void SambaConfig::tfDirectoryMode_onEditingFinished(QString text)
{
    vConfigs[1].configs.at(configName.DIRECTORY_MODE)=text;
}

void SambaConfig::chbBrowseable_onClicked(bool checked)
{
    setSettingFromCheckboxes(1,configName.BROWSEABLE,checked);
}

void SambaConfig::chbWritable_onClicked(bool checked)
{
    setSettingFromCheckboxes(1,configName.WRITABLE,checked);
}

void SambaConfig::chbGuestOk_onClicked(bool checked)
{
    setSettingFromCheckboxes(1,configName.GUEST_OK,checked);
}

void SambaConfig::chbReadOnly_onClicked(bool checked)
{
    setSettingFromCheckboxes(1,configName.READ_ONLY,checked);
}

void SambaConfig::setCommentTextField(QObject* obj)
{
    nameTextField = obj;
}

void SambaConfig::setPathTextField(QObject* obj)
{
    pathTextField = obj;
}

void SambaConfig::setCreateModeTextField(QObject* obj)
{
    createModeTextField = obj;
}

void SambaConfig::setDirectoryModeTextField(QObject* obj)
{
    directoryModeTextField = obj;
}

void SambaConfig::setBrowsableCheckBox(QObject* obj)
{
    browsableCheckBox = obj;
}

void SambaConfig::setWritablecheckBox(QObject* obj)
{
    writablecheckBox = obj;
}

void SambaConfig::setGuestOkCheckBox(QObject* obj)
{
    guestOkCheckBox = obj;
}

void SambaConfig::setReadOnlyCheckBox(QObject* obj)
{
    readOnlyCheckBox = obj;
}
