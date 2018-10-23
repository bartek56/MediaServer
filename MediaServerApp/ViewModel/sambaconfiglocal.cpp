#include "sambaconfig.h"
#include <QObject>

void SambaConfig::setCommentTextField(QObject* obj)
{
    commentTextField = QSharedPointer<QObject>(obj);
}

void SambaConfig::setPathTextField(QObject* obj)
{
    pathTextField = QSharedPointer<QObject>(obj);
}

void SambaConfig::setCreateModeTextField(QObject* obj)
{
    createModeTextField = QSharedPointer<QObject>(obj);
}

void SambaConfig::setDirectoryModeTextField(QObject* obj)
{
    directoryModeTextField = QSharedPointer<QObject>(obj);
}

void SambaConfig::setBrowsableCheckBox(QObject* obj)
{
    browsableCheckBox = QSharedPointer<QObject>(obj);
}

void SambaConfig::setWritablecheckBox(QObject* obj)
{
    writablecheckBox = QSharedPointer<QObject>(obj);
}

void SambaConfig::setGuestOkCheckBox(QObject* obj)
{
    guestOkCheckBox = QSharedPointer<QObject>(obj);
}

