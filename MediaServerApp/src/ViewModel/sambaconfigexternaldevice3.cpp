#include "sambaconfig.h"


void SambaConfig::tfName3_onEditingFinished(QString text)
{
    shareConfig4.comment = text;
}
void SambaConfig::tfPath3_onEditingFinished(QString text)
{
    shareConfig4.path = text;
}

void SambaConfig::tfCreateMode3_onEditingFinished(QString text)
{
    shareConfig4.createMode = text;
}

void SambaConfig::tfDirectoryMode3_onEditingFinished(QString text)
{
    shareConfig4.directoryMode = text;
}

void SambaConfig::chbBrowseable3_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig4.browseable, checked);
}

void SambaConfig::chbWritable3_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig4.writable, checked);
}

void SambaConfig::chbGuestOk3_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig4.guestOk, checked);
}

void SambaConfig::chbReadOnly3_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig4.readOnly, checked);
}

void SambaConfig::setCommentTextField3(QObject *obj)
{
    sambaShare4.nameTextField = obj;
}

void SambaConfig::setPathTextField3(QObject *obj)
{
    sambaShare4.pathTextField = obj;
}

void SambaConfig::setCreateModeTextField3(QObject *obj)
{
    sambaShare4.createModeTextField = obj;
}

void SambaConfig::setDirectoryModeTextField3(QObject *obj)
{
    sambaShare4.directoryModeTextField = obj;
}

void SambaConfig::setBrowsableCheckBox3(QObject *obj)
{
    sambaShare4.browsableCheckBox = obj;
}

void SambaConfig::setWritablecheckBox3(QObject *obj)
{
    sambaShare4.writablecheckBox = obj;
}

void SambaConfig::setGuestOkCheckBox3(QObject *obj)
{
    sambaShare4.guestOkCheckBox = obj;
}

void SambaConfig::setReadOnlyCheckBox3(QObject *obj)
{
    sambaShare4.readOnlyCheckBox = obj;
}

void SambaConfig::setEnabled3(QObject *obj)
{
    sambaShare4.enabledCheckBox = obj;
}
