#include "sambaconfig.h"


void SambaConfig::tfName1_onEditingFinished(QString text)
{
    vConfigs[2].name="["+text+"]";
}

void SambaConfig::tfPath1_onEditingFinished(QString text)
{
    vConfigs[2].configs.at(configName.PATH)=text;
}

void SambaConfig::tfCreateMode1_onEditingFinished(QString text)
{
    vConfigs[2].configs.at(configName.CREATE_MODE)=text;
}

void SambaConfig::tfDirectoryMode1_onEditingFinished(QString text)
{
    vConfigs[2].configs.at(configName.DIRECTORY_MODE)=text;
}

void SambaConfig::chbBrowseable1_onClicked(bool checked)
{
    setSettingFromCheckboxes(2,configName.BROWSEABLE,checked);
}

void SambaConfig::chbWritable1_onClicked(bool checked)
{
    setSettingFromCheckboxes(2,configName.WRITABLE,checked);
}

void SambaConfig::chbGuestOk1_onClicked(bool checked)
{
    setSettingFromCheckboxes(2,configName.GUEST_OK,checked);
}

void SambaConfig::chbReadOnly1_onClicked(bool checked)
{
    setSettingFromCheckboxes(2,configName.READ_ONLY,checked);
}

void SambaConfig::setCommentTextField1(QObject* obj)
{
    nameTextField1 = obj;
}

void SambaConfig::setPathTextField1(QObject* obj)
{
    pathTextField1 = obj;
}

void SambaConfig::setCreateModeTextField1(QObject* obj)
{
    createModeTextField1 = obj;
}

void SambaConfig::setDirectoryModeTextField1(QObject* obj)
{
    directoryModeTextField1 = obj;
}

void SambaConfig::setBrowsableCheckBox1(QObject* obj)
{
    browsableCheckBox1 = obj;
}

void SambaConfig::setWritablecheckBox1(QObject* obj)
{
    writablecheckBox1 = obj;
}

void SambaConfig::setGuestOkCheckBox1(QObject* obj)
{
    guestOkCheckBox1 = obj;
}

void SambaConfig::setReadOnlyCheckBox1(QObject* obj)
{
    readOnlyCheckBox1 = obj;
}
