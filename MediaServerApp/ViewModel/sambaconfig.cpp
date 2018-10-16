#include "sambaconfig.h"
#include <QDebug>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{

}

void SambaConfig::bSave_onClicked(QString text)
{
    qDebug() << "Clicked "+text;

}
