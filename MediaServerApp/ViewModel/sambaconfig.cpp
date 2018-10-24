#include "sambaconfig.h"

#include <QDebug>
#include <QProcess>
#include <QObject>
#include <QFile>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{

}


void SambaConfig::checkExternalDisks()
{
    QFile file ("/dev/sda");
    countExternalDevice=0;
    if(file.exists())
    {
        externalDiskTabButton1->setProperty("visible",QVariant(true));
        countExternalDevice++;
    }
    else
    {
        externalDiskTabButton1->setProperty("visible",QVariant(false));
    }
}

void SambaConfig::openFile()
{
    vConfigs = editFile.OpenFile("/etc/samba/smb.conf");
    loadGlobalConfigs();
    loadLocalConfigs();

    if(countExternalDevice==1)
    {
        loadExternalDisk1Configs();
    }
    else
    {
        while(vConfigs.size()>2)
        {
            auto it = vConfigs.end();
            vConfigs.erase(it);
        }
    }
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

void SambaConfig::loadExternalDisk1Configs()
{
    if(vConfigs.size() < 3)
    {
        std::map<QString, QString> mConfigsParameters;
        mConfigsParameters.insert(std::make_pair(configName.PATH,"/home/Samba"));
        mConfigsParameters.insert(std::make_pair(configName.COMMENT,"ExternalDisk1"));
        mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
        mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
        mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
        vConfigs.push_back(ConfigsName("[ExternalDisk1]",mConfigsParameters));
    }

    auto localConfig = vConfigs[2];
    auto configsParameters = localConfig.configs;

    commentTextField1->setProperty("text", QVariant(configsParameters.at(configName.COMMENT)));
    pathTextField1->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    createModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));

    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox1);
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

void SambaConfig::setExternalDiskTabButton1(QObject* obj)
{
    //externalDeviceTabButtona = QSharedPointer<QObject>(obj);
    externalDiskTabButton1 = obj;
}

void SambaConfig::setExternalDiskTabButton2(QObject* obj)
{
    externalDiskTabButton2 = QSharedPointer<QObject>(obj);
}

void SambaConfig::setExternalDiskTabButton3(QObject* obj)
{
    externalDiskTabButton3 = QSharedPointer<QObject>(obj);
}


