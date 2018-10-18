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
    auto configs = editFile.OpenFile("/etc/samba/smb.conf");

    auto globalConfig = configs[0];
    workGroupTextField->setProperty("text",QVariant(globalConfig.name));

    auto configsParameters = globalConfig.configs;
    serverStringTextField->setProperty("text",QVariant(configsParameters.at("server string")));
    netBiosTextField->setProperty("text",QVariant(configsParameters.at("netbios name")));
}

void SambaConfig::setWorkGroupTextField(QObject* obj)
{
    workGroupTextField = QSharedPointer<QObject>(obj);
}

void SambaConfig::setServerStringTextField(QObject *obj)
{
    serverStringTextField = QSharedPointer<QObject>(obj);
}
void SambaConfig::setNetBiosTextField(QObject *obj)
{
    netBiosTextField = QSharedPointer<QObject>(obj);
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
