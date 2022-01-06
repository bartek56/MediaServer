#include "sambaconfig.h"


void SambaConfig::tfName1_onEditingFinished(QString text)
{
    shareConfig1.comment = text;
}

void SambaConfig::tfPath1_onEditingFinished(QString text)
{
    shareConfig1.path = text;
}

void SambaConfig::tfCreateMode1_onEditingFinished(QString text)
{
    shareConfig1.createMode = text;
}

void SambaConfig::tfDirectoryMode1_onEditingFinished(QString text)
{
    shareConfig1.directoryMode = text;
}

void SambaConfig::chbBrowseable1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.browseable, checked);
}

void SambaConfig::chbWritable1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.writable, checked);
}

void SambaConfig::chbGuestOk1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.guestOk, checked);
}

void SambaConfig::chbReadOnly1_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig1.readOnly, checked);
}

void SambaConfig::setCommentTextField1(QObject *obj)
{
    nameTextField1 = obj;
}

void SambaConfig::setPathTextField1(QObject *obj)
{
    pathTextField1 = obj;
}

void SambaConfig::setCreateModeTextField1(QObject *obj)
{
    createModeTextField1 = obj;
}

void SambaConfig::setDirectoryModeTextField1(QObject *obj)
{
    directoryModeTextField1 = obj;
}

void SambaConfig::setBrowsableCheckBox1(QObject *obj)
{
    browsableCheckBox1 = obj;
}

void SambaConfig::setWritablecheckBox1(QObject *obj)
{
    writablecheckBox1 = obj;
}

void SambaConfig::setGuestOkCheckBox1(QObject *obj)
{
    guestOkCheckBox1 = obj;
}

void SambaConfig::setReadOnlyCheckBox1(QObject *obj)
{
    readOnlyCheckBox1 = obj;
}

void SambaConfig::setEnabled1(QObject *obj)
{
    enabledCheckBox1 = obj;
}
