#include "sambaconfig.h"

#include <QDebug>
#include <QProcess>
#include <QObject>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{

}

void SambaConfig::openFile()
{
    vConfigs = editFile.OpenFile("/etc/samba/smb.conf");
    loadGlobalConfigs();
    loadLocalConfigs();
}

void SambaConfig::loadLocalConfigs()
{
    auto localConfig = vConfigs[1];
    auto configsParameters = localConfig.configs;

    commentTextField->setProperty("text", QVariant(configsParameters.at(configName.COMMENT)));
    pathTextField->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    createModeTextField->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));

    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox);

}

void SambaConfig::loadGlobalConfigs()
{
    auto globalConfig = vConfigs[0];
    auto configsParameters = globalConfig.configs;

    workGroupTextField->setProperty("text",QVariant(configsParameters.at(configName.WORKGROUP)));
    serverStringTextField->setProperty("text",QVariant(configsParameters.at(configName.SERVER_STRING)));
    netBiosTextField->setProperty("text",QVariant(configsParameters.at(configName.NETBIOS_NAME)));

    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), globalBrowsableCheckBox);
    setCheckboxesFromFileSettings(configsParameters.at(configName.LOCAL_MASTER), localMastercheckBox);
    setCheckboxesFromFileSettings(configsParameters.at(configName.DOMAIN_MASTER), domainMasterCheckBox);
}


void SambaConfig::bSave_onClicked()
{
    editFile.SaveFile("/etc/samba/smb.conf", vConfigs);
    QProcess::execute("systemctl restart nmbd");
    QProcess::execute("systemctl restart smbd");
}

void SambaConfig::setSettingFromCheckboxes(unsigned long row, QString configName,bool checked)
{
    if(checked)
    {
        vConfigs[row].configs.at(configName) = "yes";
    }
    else
    {
        vConfigs[row].configs.at(configName) = "no";
    }
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
