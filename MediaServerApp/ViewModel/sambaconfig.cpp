#include "sambaconfig.h"

#include <QDebug>

#include <QObject>
#include <QFile>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{

}

void SambaConfig::checkExternalDisks()
{
    QFile file ("/dev/sda");
    if(file.exists())
    {
        externalDisk1IsConnected=true;
        externalDiskTabButton1->setProperty("visible",QVariant(true));
    }
    else
    {
        externalDisk1IsConnected=false;
        externalDiskTabButton1->setProperty("visible",QVariant(false));
    }


    QFile file2 ("/dev/sdb");
    if(file2.exists())
    {
        externalDisk2IsConnected=true;
        externalDiskTabButton2->setProperty("visible",QVariant(true));
    }
    else
    {
        externalDisk2IsConnected=false;
        externalDiskTabButton2->setProperty("visible",QVariant(false));
    }

    QFile file3 ("/dev/sdc");
    if(file3.exists())
    {
        externalDisk3IsConnected=true;
        externalDiskTabButton3->setProperty("visible",QVariant(true));
    }
    else
    {
        externalDisk3IsConnected=false;
        externalDiskTabButton3->setProperty("visible",QVariant(false));
    }
}

void SambaConfig::openFile()
{
    vConfigs = editFile.OpenFile("/etc/samba/smb.conf");
    loadGlobalConfigs();
    loadLocalConfigs();

    if(externalDisk1IsConnected)
    {
        loadExternalDisk1Configs();
    }

    if(externalDisk2IsConnected)
    {
        loadExternalDisk2Configs();
    }

    if(externalDisk3IsConnected)
    {
        loadExternalDisk3Configs();
    }

}

void SambaConfig::loadLocalConfigs()
{
    auto localConfig = vConfigs[1];
    auto configsParameters = localConfig.configs;

    nameTextField->setProperty("text", QVariant(configsParameters.at(configName.COMMENT)));
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
    int index = indexOfExternalDiskConfiguration("sda");

    if(index==0)
    {
        std::map<QString, QString> mConfigsParameters;
        mConfigsParameters.insert(std::make_pair(configName.PATH,"/mnt/externalDisk1"));
        mConfigsParameters.insert(std::make_pair(configName.COMMENT,"sda"));
        mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
        mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
        mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
        vConfigs.push_back(ConfigsName("[ExternalDisk1]",mConfigsParameters));
        QProcess::execute("mount /dev/sda1 /mnt/externalDisk1");
        externalDisk1IsMounted=true;
    }

    auto localConfig = vConfigs[2];
    auto configsParameters = localConfig.configs;

    nameTextField1->setProperty("text", QVariant(localConfig.name));
    pathTextField1->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    createModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));

    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox1);
}

void SambaConfig::loadExternalDisk2Configs()
{
    int index = indexOfExternalDiskConfiguration("sdb");

    if(index==0)
    {
        std::map<QString, QString> mConfigsParameters;
        mConfigsParameters.insert(std::make_pair(configName.PATH,"/mnt/externalDisk2"));
        mConfigsParameters.insert(std::make_pair(configName.COMMENT,"sdb"));
        mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
        mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
        mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
        vConfigs.push_back(ConfigsName("[ExternalDisk2]",mConfigsParameters));
        QProcess::execute("mount /dev/sdb1 /mnt/externalDisk2");
        externalDisk2IsMounted=true;
    }

    auto localConfig = vConfigs[3];
    auto configsParameters = localConfig.configs;

    nameTextField2->setProperty("text", QVariant(localConfig.name));
    pathTextField2->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    createModeTextField2->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField2->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));

    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox2);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox2);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox2);
}

void SambaConfig::loadExternalDisk3Configs()
{
    int index = indexOfExternalDiskConfiguration("sdc");

    if(index==0)
    {
        std::map<QString, QString> mConfigsParameters;
        mConfigsParameters.insert(std::make_pair(configName.PATH,"/mnt/externalDisk3"));
        mConfigsParameters.insert(std::make_pair(configName.COMMENT,"sdc"));
        mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
        mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
        mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
        mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
        vConfigs.push_back(ConfigsName("[ExternalDisk3]",mConfigsParameters));
        QProcess::execute("mount /dev/sdc1 /mnt/externalDisk3");
        externalDisk2IsMounted=true;
    }

    auto localConfig = vConfigs[4];
    auto configsParameters = localConfig.configs;

    nameTextField3->setProperty("text", QVariant(localConfig.name));
    pathTextField3->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    createModeTextField3->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField3->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));

    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox3);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox3);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox3);
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
    externalDiskTabButton2 = obj;
}

void SambaConfig::setExternalDiskTabButton3(QObject* obj)
{
    externalDiskTabButton3 = obj;
}

void SambaConfig::bUmount1_onClicked()
{
    QProcess::execute("umount /dev/sda1");
    externalDisk1IsMounted=false;
    removeConfig("sda");
    externalDiskTabButton1->setProperty("visible",QVariant(false));
    stackLayout->setProperty("currentIndex", 1);
}

void SambaConfig::bUmount2_onClicked()
{
    QProcess::execute("umount /dev/sdb1");
    externalDisk2IsMounted=false;
    removeConfig("sdb");
    externalDiskTabButton2->setProperty("visible",QVariant(false));
    stackLayout->setProperty("currentIndex", 1);
}

void SambaConfig::bUmount3_onClicked()
{
    QProcess::execute("umount /dev/sdc1");
    externalDisk3IsMounted=false;
    removeConfig("sdc");
    externalDiskTabButton3->setProperty("visible",QVariant(false));
    stackLayout->setProperty("currentIndex", 1);
}

void SambaConfig::removeConfig(QString const comment)
{
    auto iter=vConfigs.begin();
    iter++;
    iter++;
    for (iter; iter != vConfigs.end();++iter)
    {
        auto map = iter->configs;
        QString con = map.at(configName.COMMENT);
        if(con==comment)
        {
            vConfigs.erase(iter);
            return;
        }
    }

    editFile.SaveFile("/etc/samba/smb.conf", vConfigs);
    QProcess::execute("systemctl restart nmbd");
    QProcess::execute("systemctl restart smbd");
}

int SambaConfig::indexOfExternalDiskConfiguration(QString comment)
{
    int index=1;
    auto iter=vConfigs.begin();
    iter++;
    iter++;
    for (iter; iter != vConfigs.end();++iter)
    {
        auto map = iter->configs;
        QString name = map.at(configName.COMMENT);
        if(name==comment)
        {
            return index;
        }
        index++;
    }
    return 0;
}
