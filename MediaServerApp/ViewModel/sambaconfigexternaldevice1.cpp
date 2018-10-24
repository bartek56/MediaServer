#include "sambaconfig.h"




void SambaConfig::setCommentTextField1(QObject* obj)
{
    commentTextField1 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setPathTextField1(QObject* obj)
{
    pathTextField1 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setCreateModeTextField1(QObject* obj)
{
    createModeTextField1 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setDirectoryModeTextField1(QObject* obj)
{
    directoryModeTextField1 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setBrowsableCheckBox1(QObject* obj)
{
    browsableCheckBox1 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setWritablecheckBox1(QObject* obj)
{
    writablecheckBox1 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setGuestOkCheckBox1(QObject* obj)
{
    guestOkCheckBox1 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setReadOnlyCheckBox1(QObject* obj)
{
    readOnlyCheckBox1 = QSharedPointer<QObject>(obj);
}
