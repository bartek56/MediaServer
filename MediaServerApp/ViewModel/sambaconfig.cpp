#include "sambaconfig.h"
#include "editfile.h"
#include <QDebug>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{
    EditFile editFile;
    auto configsMap = editFile.OpenFile("/etc/samba/smb.conf");

}

void SambaConfig::bSave_onClicked(QString text)
{
    qDebug() << "Clicked "+text;
}
