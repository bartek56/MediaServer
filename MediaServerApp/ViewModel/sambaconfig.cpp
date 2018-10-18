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
    auto configsParameters = globalConfig.configs;

    workGroupTextField->setProperty("text",QVariant(configsParameters.at("workgroup")));
    serverStringTextField->setProperty("text",QVariant(configsParameters.at("server string")));
    netBiosTextField->setProperty("text",QVariant(configsParameters.at("netbios name")));

    setCheckboxesFromFileSettings(configsParameters.at("browseable"), browsableCheckBox);
    setCheckboxesFromFileSettings(configsParameters.at("local master"), localMastercheckBox);
    setCheckboxesFromFileSettings(configsParameters.at("domain master"), domainMasterCheckBox);
}


void SambaConfig::setCheckboxesFromFileSettings(const QString configsParameters, QSharedPointer<QObject> checkbox)
{
    if(!configsParameters.compare("yes"))
    {
        checkbox->setProperty("checked",QVariant(true));
    }
    else
    {
        checkbox->setProperty("checked",QVariant(false));
    }
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
void SambaConfig::setBrowsableCheckBox(QObject *obj)
{
    browsableCheckBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setLocalMastercheckBox(QObject *obj)
{
    localMastercheckBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setDomainMasterCheckBox(QObject *obj)
{
    domainMasterCheckBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setSecurityComboBox(QObject *obj)
{
    securityComboBox = QSharedPointer<QObject>(obj);
}
void SambaConfig::setMapToGuestComboBox(QObject *obj)
{
    mapToGuestComboBox = QSharedPointer<QObject>(obj);
}

