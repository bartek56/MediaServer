#include "sambaconfig.h"
#include <QObject>


void SambaConfig::tfName_onEditingFinished(QString text)
{
    localConfig.comment = text;
}

void SambaConfig::tfCreateMode_onEditingFinished(QString text)
{
    localConfig.createMode = text;
}

void SambaConfig::tfDirectoryMode_onEditingFinished(QString text)
{
    localConfig.directoryMode = text;
}

void SambaConfig::chbBrowseable_onClicked(bool checked)
{
    setSettingFromCheckboxes(localConfig.browseable, checked);
}

void SambaConfig::chbWritable_onClicked(bool checked)
{
    setSettingFromCheckboxes(localConfig.writable, checked);
}

void SambaConfig::chbGuestOk_onClicked(bool checked)
{
    setSettingFromCheckboxes(localConfig.guestOk, checked);
}

void SambaConfig::chbReadOnly_onClicked(bool checked)
{
    setSettingFromCheckboxes(localConfig.readOnly, checked);
}

void SambaConfig::setCommentTextField(QObject *obj)
{
    nameTextField = obj;
}

void SambaConfig::setPathTextField(QObject *obj)
{
    pathTextField = obj;
}

void SambaConfig::setCreateModeTextField(QObject *obj)
{
    createModeTextField = obj;
}

void SambaConfig::setDirectoryModeTextField(QObject *obj)
{
    directoryModeTextField = obj;
}

void SambaConfig::setBrowsableCheckBox(QObject *obj)
{
    browsableCheckBox = obj;
}

void SambaConfig::setWritablecheckBox(QObject *obj)
{
    writablecheckBox = obj;
}

void SambaConfig::setGuestOkCheckBox(QObject *obj)
{
    guestOkCheckBox = obj;
}

void SambaConfig::setReadOnlyCheckBox(QObject *obj)
{
    readOnlyCheckBox = obj;
}
