#include "sambaconfig.h"
#include <QObject>


void SambaConfig::tfName_onEditingFinished(QString text)
{
    shareConfig1.comment = text;
}

void SambaConfig::tfCreateMode_onEditingFinished(QString text)
{
    shareConfig1.createMode = text;
}

void SambaConfig::tfDirectoryMode_onEditingFinished(QString text)
{
    shareConfig1.directoryMode = text;
}

void SambaConfig::chbBrowseable_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.browseable, checked);
}

void SambaConfig::chbWritable_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.writable, checked);
}

void SambaConfig::chbGuestOk_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.guestOk, checked);
}

void SambaConfig::chbReadOnly_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.readOnly, checked);
}

void SambaConfig::setCommentTextField(QObject *obj)
{
    sambaShare1.nameTextField = obj;
}

void SambaConfig::setPathTextField(QObject *obj)
{
    sambaShare1.pathTextField = obj;
}

void SambaConfig::setCreateModeTextField(QObject *obj)
{
    sambaShare1.createModeTextField = obj;
}

void SambaConfig::setDirectoryModeTextField(QObject *obj)
{
    sambaShare1.directoryModeTextField = obj;
}

void SambaConfig::setBrowsableCheckBox(QObject *obj)
{
    sambaShare1.browsableCheckBox = obj;
}

void SambaConfig::setWritablecheckBox(QObject *obj)
{
    sambaShare1.writablecheckBox = obj;
}

void SambaConfig::setGuestOkCheckBox(QObject *obj)
{
    sambaShare1.guestOkCheckBox = obj;
}

void SambaConfig::setReadOnlyCheckBox(QObject *obj)
{
    sambaShare1.readOnlyCheckBox = obj;
}
