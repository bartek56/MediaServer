#include "sambaconfig.h"


void SambaConfig::tfName2_onEditingFinished(QString text)
{
    shareConfig2.comment = text;
}

void SambaConfig::tfPath2_onEditingFinished(QString text)
{
    shareConfig2.path = text;
}

void SambaConfig::tfCreateMode2_onEditingFinished(QString text)
{
    shareConfig2.createMode = text;
}

void SambaConfig::tfDirectoryMode2_onEditingFinished(QString text)
{
    shareConfig2.directoryMode = text;
}

void SambaConfig::chbBrowseable2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.browseable, checked);
}

void SambaConfig::chbWritable2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.writable, checked);
}

void SambaConfig::chbGuestOk2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.guestOk, checked);
}

void SambaConfig::chbReadOnly2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig2.readOnly, checked);
}

void SambaConfig::setCommentTextField2(QObject *obj)
{
    nameTextField2 = obj;
}

void SambaConfig::setPathTextField2(QObject *obj)
{
    pathTextField2 = obj;
}

void SambaConfig::setCreateModeTextField2(QObject *obj)
{
    createModeTextField2 = obj;
}

void SambaConfig::setDirectoryModeTextField2(QObject *obj)
{
    directoryModeTextField2 = obj;
}

void SambaConfig::setBrowsableCheckBox2(QObject *obj)
{
    browsableCheckBox2 = obj;
}

void SambaConfig::setWritablecheckBox2(QObject *obj)
{
    writablecheckBox2 = obj;
}

void SambaConfig::setGuestOkCheckBox2(QObject *obj)
{
    guestOkCheckBox2 = obj;
}

void SambaConfig::setReadOnlyCheckBox2(QObject *obj)
{
    readOnlyCheckBox2 = obj;
}

void SambaConfig::setEnabled2(QObject *obj)
{
    enabledCheckBox2 = obj;
}
