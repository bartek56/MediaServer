#include "SambaConfig.h"


void SambaConfig::tfName1_onEditingFinished(QString text)
{
    shareConfig2.comment = text;
}

void SambaConfig::tfPath1_onEditingFinished(QString text)
{
    shareConfig2.path = text;
}

void SambaConfig::tfCreateMode1_onEditingFinished(QString text)
{
    shareConfig2.createMode = text;
}

void SambaConfig::tfDirectoryMode1_onEditingFinished(QString text)
{
    shareConfig2.directoryMode = text;
}

void SambaConfig::chbBrowseable1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.browseable, checked);
}

void SambaConfig::chbWritable1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.writable, checked);
}

void SambaConfig::chbGuestOk1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.guestOk, checked);
}

void SambaConfig::chbReadOnly1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.readOnly, checked);
}

void SambaConfig::setCommentTextField1(QObject *obj)
{
    sambaShare2.nameTextField = obj;
}

void SambaConfig::setPathTextField1(QObject *obj)
{
    sambaShare2.pathTextField = obj;
}

void SambaConfig::setCreateModeTextField1(QObject *obj)
{
    sambaShare2.createModeTextField = obj;
}

void SambaConfig::setDirectoryModeTextField1(QObject *obj)
{
    sambaShare2.directoryModeTextField = obj;
}

void SambaConfig::setBrowsableCheckBox1(QObject *obj)
{
    sambaShare2.browsableCheckBox = obj;
}

void SambaConfig::setWritablecheckBox1(QObject *obj)
{
    sambaShare2.writablecheckBox = obj;
}

void SambaConfig::setGuestOkCheckBox1(QObject *obj)
{
    sambaShare2.guestOkCheckBox = obj;
}

void SambaConfig::setReadOnlyCheckBox1(QObject *obj)
{
    sambaShare2.readOnlyCheckBox = obj;
}

void SambaConfig::setEnabled1(QObject *obj)
{
    sambaShare2.enabledCheckBox = obj;
}
