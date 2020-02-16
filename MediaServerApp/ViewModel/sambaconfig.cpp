#include "sambaconfig.h"

#include <QDebug>
#include <QObject>
#include <QFile>

SambaConfig::SambaConfig(QObject *parent) : QObject(parent)
{

}

void SambaConfig::checkService(QObject *saveButton)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("bash", QStringList() << "-c" << "systemctl is-active nmb");
    process.setReadChannel(QProcess::StandardOutput);
    QStringList devicesList;
    process.waitForFinished();
    auto text = process.readAll();
    process.close();
    saveButton->setProperty("enabled",QVariant(!text.contains("in")));
}

void SambaConfig::loadAllConfigs()
{
    vConfigs = editFile.OpenFile("/etc/samba/smb.conf");
    auto countShare = vConfigs.size();

    showGlobalConfigs();
    showLocalConfigs();
    if(countShare==2)
    {
        saveDefaultConfigsForExternalDisk1();
        saveDefaultConfigsForExternalDisk2();
        saveDefaultConfigsForExternalDisk3();
    }
    else if(countShare==3)
    {
        enabledCheckBox1->setProperty("checked", QVariant(true));
        saveDefaultConfigsForExternalDisk2();
        saveDefaultConfigsForExternalDisk3();
    }
    else if(countShare==4)
    {
        enabledCheckBox1->setProperty("checked", QVariant(true));
        enabledCheckBox2->setProperty("checked", QVariant(true));
        saveDefaultConfigsForExternalDisk3();

    }
    else if(countShare==5)
    {
        enabledCheckBox1->setProperty("checked", QVariant(true));
        enabledCheckBox2->setProperty("checked", QVariant(true));
        enabledCheckBox3->setProperty("checked", QVariant(true));
    }

    showConfigsForExternalDisk1();
    showConfigsForExternalDisk2();
    showConfigsForExternalDisk3();

}

void SambaConfig::showLocalConfigs()
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

void SambaConfig::showGlobalConfigs()
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

void SambaConfig::saveDefaultConfigsForExternalDisk1()
{
    std::map<QString, QString> mConfigsParameters;
    mConfigsParameters.insert(std::make_pair(configName.PATH,"/mnt/externalDisk1"));
    mConfigsParameters.insert(std::make_pair(configName.COMMENT,"DISK1"));
    mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
    mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
    mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
    vConfigs.push_back(SambaConfigsName("[DISK1]",mConfigsParameters));
}

void SambaConfig::saveDefaultConfigsForExternalDisk2()
{
    std::map<QString, QString> mConfigsParameters;
    mConfigsParameters.insert(std::make_pair(configName.PATH,"/mnt/externalDisk2"));
    mConfigsParameters.insert(std::make_pair(configName.COMMENT,"DISK2"));
    mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
    mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
    mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
    vConfigs.push_back(SambaConfigsName("[DISK2]",mConfigsParameters));
}

void SambaConfig::saveDefaultConfigsForExternalDisk3()
{
    std::map<QString, QString> mConfigsParameters;
    mConfigsParameters.insert(std::make_pair(configName.PATH,"/mnt/externalDisk3"));
    mConfigsParameters.insert(std::make_pair(configName.COMMENT,"DISK3"));
    mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
    mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
    mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
    vConfigs.push_back(SambaConfigsName("[DISK3]",mConfigsParameters));
}

void SambaConfig::showConfigsForExternalDisk1()
{
    externalDiskTabButton1->setProperty("visible",QVariant(true));
    auto localConfig = vConfigs[2];
    auto configsParameters = localConfig.configs;

    createModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));
    pathTextField1->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    auto name = localConfig.name;
    name.remove(0,1);
    name.remove(name.length()-1,1);

    nameTextField1->setProperty("text", QVariant(name));
    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.READ_ONLY), readOnlyCheckBox1);
}

void SambaConfig::showConfigsForExternalDisk2()
{
    externalDiskTabButton2->setProperty("visible",QVariant(true));
    auto localConfig = vConfigs[3];
    auto configsParameters = localConfig.configs;
    createModeTextField2->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    pathTextField2->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    auto name = localConfig.name;
    name.remove(0,1);
    name.remove(name.length()-1,1);

    nameTextField2->setProperty("text", QVariant(name));
    directoryModeTextField2->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));
    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox2);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox2);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox2);
    setCheckboxesFromFileSettings(configsParameters.at(configName.READ_ONLY), readOnlyCheckBox2);
}

void SambaConfig::showConfigsForExternalDisk3()
{
    externalDiskTabButton3->setProperty("visible",QVariant(true));
    auto localConfig = vConfigs[4];
    auto configsParameters = localConfig.configs;
    createModeTextField3->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField3->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));
    pathTextField3->setProperty("text", QVariant(configsParameters.at(configName.PATH)));
    auto name = localConfig.name;
    name.remove(0,1);
    name.remove(name.length()-1,1);

    nameTextField3->setProperty("text", QVariant(name));
    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox3);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox3);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox3);
    setCheckboxesFromFileSettings(configsParameters.at(configName.READ_ONLY), readOnlyCheckBox3);
}

void SambaConfig::bSave_onClicked()
{
    if(!enabledCheckBox1->property("checked").toBool())
    {
        auto index = indexOfExternalDiskConfigurationByName(nameTextField1->property("text").toString());
        if(index!=0)
            vConfigs.erase (vConfigs.begin()+index);
    }
    if(!enabledCheckBox2->property("checked").toBool())
    {
        auto index = indexOfExternalDiskConfigurationByName(nameTextField2->property("text").toString());
        if(index!=0)
            vConfigs.erase (vConfigs.begin()+index);
    }
    if(!enabledCheckBox3->property("checked").toBool())
    {
        auto index = indexOfExternalDiskConfigurationByName(nameTextField3->property("text").toString());
        if(index!=0)
            vConfigs.erase (vConfigs.begin()+index);
    }
    editFile.SaveFile("/etc/samba/smb.conf", vConfigs);
    QProcess::execute("systemctl restart nmb");
    QProcess::execute("systemctl restart smb");
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

void SambaConfig::setCheckboxesFromFileSettings(const QString configsParameters, QObject* checkbox)
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

unsigned int SambaConfig::indexOfExternalDiskConfiguration(QString comment)
{
    unsigned int index=2;
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

unsigned int SambaConfig::indexOfExternalDiskConfigurationByName(QString name)
{
    unsigned int index=2;
    auto iter=vConfigs.begin();
    iter++;
    iter++;
    for (iter; iter != vConfigs.end();++iter)
    {
        auto configName = iter->name;
        if(configName.contains(name))
        {
            return index;
        }
        index++;
    }
    return 0;
}

void SambaConfig::bFileDialog_onAccepted(QString catalog)
{
    QString path = catalog.remove(0,7);
    pathTextField->setProperty("text",QVariant(path));
    vConfigs[1].configs.at(configName.PATH)=path;
}

void SambaConfig::bFileDialog1_onAccepted(QString catalog)
{
    QString path = catalog.remove(0,7);
    pathTextField1->setProperty("text",QVariant(path));
    vConfigs[2].configs.at(configName.PATH)=path;
}

void SambaConfig::bFileDialog2_onAccepted(QString catalog)
{
    QString path = catalog.remove(0,7);
    pathTextField2->setProperty("text",QVariant(path));
    vConfigs[3].configs.at(configName.PATH)=path;
}

void SambaConfig::bFileDialog3_onAccepted(QString catalog)
{
    QString path = catalog.remove(0,7);
    pathTextField3->setProperty("text",QVariant(path));
    vConfigs[4].configs.at(configName.PATH)=path;
}
