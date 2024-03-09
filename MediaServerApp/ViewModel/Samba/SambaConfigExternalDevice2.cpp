#include "SambaConfig.h"


void SambaConfig::tfName2_onEditingFinished(QString text)
{
    shareConfig3.comment = text;
}

void SambaConfig::tfPath2_onEditingFinished(QString text)
{
    shareConfig3.path = text;
}

void SambaConfig::tfCreateMode2_onEditingFinished(QString text)
{
    shareConfig3.createMode = text;
}

void SambaConfig::tfDirectoryMode2_onEditingFinished(QString text)
{
    shareConfig3.directoryMode = text;
}

void SambaConfig::chbBrowseable2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig3.browseable, checked);
}

void SambaConfig::chbWritable2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig3.writable, checked);
}

void SambaConfig::chbGuestOk2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig3.guestOk, checked);
}

void SambaConfig::chbReadOnly2_onClicked(bool checked)
{
    setSettingFromCheckboxes(shareConfig3.readOnly, checked);
}

void SambaConfig::setCommentTextField2(QObject *obj)
{
    sambaShare3.nameTextField = obj;
}

void SambaConfig::setPathTextField2(QObject *obj)
{
    sambaShare3.pathTextField = obj;
}

void SambaConfig::setCreateModeTextField2(QObject *obj)
{
    sambaShare3.createModeTextField = obj;
}

void SambaConfig::setDirectoryModeTextField2(QObject *obj)
{
    sambaShare3.directoryModeTextField = obj;
}

void SambaConfig::setBrowsableCheckBox2(QObject *obj)
{
    sambaShare3.browsableCheckBox = obj;
}

void SambaConfig::setWritablecheckBox2(QObject *obj)
{
    sambaShare3.writablecheckBox = obj;
}

void SambaConfig::setGuestOkCheckBox2(QObject *obj)
{
    sambaShare3.guestOkCheckBox = obj;
}

void SambaConfig::setReadOnlyCheckBox2(QObject *obj)
{
    sambaShare3.readOnlyCheckBox = obj;
}

void SambaConfig::setEnabled2(QObject *obj)
{
    sambaShare3.enabledCheckBox = obj;
}
