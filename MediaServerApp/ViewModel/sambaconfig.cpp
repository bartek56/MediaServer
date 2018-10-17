#include "sambaconfig.h"
#include "editfile.h"
#include <QDebug>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{

}

void SambaConfig::bSave_onClicked(QString text)
{
    qDebug() << "Clicked "+text;
}

void SambaConfig::openFile()
{
    EditFile editFile;
    auto configsMap = editFile.OpenFile("/etc/samba/smb.conf");

    for(auto a : configsMap)
    {
        workGroupTextField->setProperty("text",QVariant(a.first));
        serverStringTextFieldMyObject->setProperty("text",QVariant(a.second.at("server string")));
    }
}

void SambaConfig::setWorkGroupTextField(QObject *obj)
{
    workGroupTextField = obj;
}

void SambaConfig::setServerStringTextField(QObject *obj)
{
    serverStringTextFieldMyObject = obj;
}
void SambaConfig::setNetBiosTextField(QObject *obj)
{
    netBiosTextField = obj;
}
/*
void SambaConfig::setBrowsableCheckBox(std::unique_ptr<QObject> obj)
{
    browsableCheckBox = std::make_unique<QObject>(obj);
}
void SambaConfig::setLocalMastercheckBox(std::unique_ptr<QObject> obj)
{
    localMastercheckBox = std::make_unique<QObject>(obj);
}
void SambaConfig::setDomainMasterCheckBox(std::unique_ptr<QObject> obj)
{
    domainMasterCheckBox = std::make_unique<QObject>(obj);
}

void SambaConfig::setSecurityComboBox(std::unique_ptr<QObject> obj)
{
    securityComboBox = std::make_unique<QObject>(obj);
}

void SambaConfig::setMapToGuestComboBox(std::unique_ptr<QObject> obj)
{
    mapToGuestComboBox = std::make_unique<QObject>(obj);
}
*/
