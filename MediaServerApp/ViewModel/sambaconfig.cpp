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

void SambaConfig::checkingIfDisksAreMounted()
{
    QFile file ("/proc/self/mounts");

    if(!file.exists() || !file.open(QIODevice::ReadOnly))
        return;

    QString line="";
    QTextStream stream(&file);

    while (!line.isNull())
    {
        line = stream.readLine();

        if(line.contains("/dev/sda1"))
        {
            externalDisk1IsMounted=true;
            //line.replace("\040"," ");
            auto parameters = line.split(' ');
            deviceMountpoint1=parameters[1];
            deviceMountpoint1.replace("\040"," ");
            pathTextField1->setProperty("text", QVariant(deviceMountpoint1));
            auto deviceName = parameters[1].remove(0,5);
            deviceName.replace("\040"," ");
            nameTextField1->setProperty("text", QVariant(deviceName));
            deviceName1=deviceName;

        }
        else if(line.contains("/dev/sdb1"))
        {
            externalDisk2IsMounted=true;
            auto parameters = line.split(' ');
            deviceMountpoint2=parameters[1];
            deviceMountpoint2.replace("\\040"," ");
            pathTextField2->setProperty("text", QVariant(deviceMountpoint2));
            auto deviceName = parameters[1].remove(0,5);
            qDebug() << deviceName;
            deviceName.replace("\\040"," ");
            qDebug() << deviceName;
            nameTextField2->setProperty("text", QVariant(deviceName));
            deviceName2=deviceName;
        }
        else if(line.contains("/dev/sdc1"))
        {
            externalDisk3IsMounted=true;
            auto parameters = line.split(' ');
            deviceMountpoint3=parameters[1];
            pathTextField3->setProperty("text", QVariant(deviceMountpoint3));
            auto deviceName = parameters[1].remove(0,5);
            nameTextField3->setProperty("text", QVariant(deviceName));
            deviceName3=deviceName;
        }
    }
}

void SambaConfig::loadConfigsExternalDisk1()
{
    unsigned int index = indexOfExternalDiskConfiguration("sda");

    if(!externalDisk1IsMounted && index!=0)
    {
        // disk is not mounted - settings are in file
        vConfigs.erase(vConfigs.begin()+index);
    }
    else if(externalDisk1IsMounted && index==0)
    {
        // disk is mounted - settings are NOT in file
        saveDefaultConfigsForExternalDisk1();
        showConfigsForExternalDisk1();
    }
    else if(externalDisk1IsMounted && index!=0)
    {
        // disk is mounted - settings are in file
        auto path = vConfigs[index].configs.at(configName.PATH);
        auto deviceName = path.remove(0,5);

        if(deviceName==deviceName1)
        {
            //it is the same disk
            showConfigsForExternalDisk1();
        }
        else
        {
             //it is other disk
            vConfigs.erase(vConfigs.begin()+index);
            saveDefaultConfigsForExternalDisk1();
            showConfigsForExternalDisk1();
        }
    }
}

void SambaConfig::loadConfigsExternalDisk2()
{
    unsigned int index = indexOfExternalDiskConfiguration("sdb");
    if(!externalDisk2IsMounted && index!=0)
    {
        // disk is not mounted - settings are in file
        vConfigs.erase(vConfigs.begin()+index);
    }
    else if(externalDisk2IsMounted && index==0)
    {
        // disk is mounted - settings are NOT in file
        saveDefaultConfigsForExternalDisk2();
        showConfigsForExternalDisk2();

    }
    else if(externalDisk2IsMounted && index!=0)
    {
        // disk is mounted - settings are in file
        auto path = vConfigs[index].configs.at(configName.PATH);
        auto deviceName = path.remove(0,5);

        if(deviceName==deviceName2)
        {
            //it is the same disk
            showConfigsForExternalDisk2();
        }
        else
        {
            //it is other disk
            vConfigs.erase(vConfigs.begin()+index);
            saveDefaultConfigsForExternalDisk2();
            showConfigsForExternalDisk2();
        }
    }
}

void SambaConfig::loadConfigsExternalDisk3()
{
    unsigned int index = indexOfExternalDiskConfiguration("sdc");
    if(!externalDisk3IsMounted && index!=0)
    {
        // disk is not mounted - settings are in file
        vConfigs.erase(vConfigs.begin()+index);
    }
    else if(externalDisk3IsMounted && index==0)
    {
        // disk is mounted - settings are NOT in file
        saveDefaultConfigsForExternalDisk3();
        showConfigsForExternalDisk3();
    }
    else if(externalDisk3IsMounted && index!=0)
    {
        // disk is mounted - settings are in file
        auto path = vConfigs[index].configs.at(configName.PATH);
        auto deviceName = path.remove(0,5);

        if(deviceName==deviceName3)
        {
            //it is the same disk
            showConfigsForExternalDisk3();
        }
        else
        {
            //it is other disk
            vConfigs.erase(vConfigs.begin()+index);
            saveDefaultConfigsForExternalDisk3();
            showConfigsForExternalDisk3();
        }
    }
}

void SambaConfig::loadAllConfigs()
{
    vConfigs = editFile.OpenFile("/etc/samba/smb.conf");
    showGlobalConfigs();
    showLocalConfigs();
    loadConfigsExternalDisk1();
    loadConfigsExternalDisk2();
    loadConfigsExternalDisk3();
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
    auto path = pathTextField1->property("text").toString();
    auto name = nameTextField1->property("text").toString();
    mConfigsParameters.insert(std::make_pair(configName.PATH,path));
    mConfigsParameters.insert(std::make_pair(configName.COMMENT,"sda"));
    mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
    mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
    mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
    vConfigs.push_back(SambaConfigsName("["+name+"]",mConfigsParameters));
}

void SambaConfig::saveDefaultConfigsForExternalDisk2()
{
    std::map<QString, QString> mConfigsParameters;
    auto path = pathTextField2->property("text").toString();
    auto name = nameTextField2->property("text").toString();
    mConfigsParameters.insert(std::make_pair(configName.PATH,path));
    mConfigsParameters.insert(std::make_pair(configName.COMMENT,"sdb"));
    mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
    mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
    mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
    vConfigs.push_back(SambaConfigsName("["+name+"]",mConfigsParameters));
}

void SambaConfig::saveDefaultConfigsForExternalDisk3()
{
    std::map<QString, QString> mConfigsParameters;
    auto path = pathTextField3->property("text").toString();
    auto name = nameTextField3->property("text").toString();
    mConfigsParameters.insert(std::make_pair(configName.PATH,path));

    mConfigsParameters.insert(std::make_pair(configName.PATH,"/mnt/externalDisk3"));
    mConfigsParameters.insert(std::make_pair(configName.COMMENT,"sdc"));
    mConfigsParameters.insert(std::make_pair(configName.BROWSEABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.WRITABLE,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.GUEST_OK,"yes"));
    mConfigsParameters.insert(std::make_pair(configName.READ_ONLY,"no"));
    mConfigsParameters.insert(std::make_pair(configName.CREATE_MODE,"0644"));
    mConfigsParameters.insert(std::make_pair(configName.DIRECTORY_MODE,"0755"));
    vConfigs.push_back(SambaConfigsName("["+name+"]",mConfigsParameters));
}

void SambaConfig::showConfigsForExternalDisk1()
{
    externalDiskTabButton1->setProperty("visible",QVariant(true));
    unsigned int index = indexOfExternalDiskConfiguration("sda");
    auto localConfig = vConfigs[index];
    auto configsParameters = localConfig.configs;
    createModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField1->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));
    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox1);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox1);
}

void SambaConfig::showConfigsForExternalDisk2()
{
    externalDiskTabButton2->setProperty("visible",QVariant(true));
    unsigned int index = indexOfExternalDiskConfiguration("sdb");
    auto localConfig = vConfigs[index];
    auto configsParameters = localConfig.configs;
    createModeTextField2->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField2->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));
    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox2);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox2);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox2);
}

void SambaConfig::showConfigsForExternalDisk3()
{
    externalDiskTabButton3->setProperty("visible",QVariant(true));
    unsigned int index = indexOfExternalDiskConfiguration("sdc");
    auto localConfig = vConfigs[index];
    auto configsParameters = localConfig.configs;
    createModeTextField3->setProperty("text", QVariant(configsParameters.at(configName.CREATE_MODE)));
    directoryModeTextField3->setProperty("text", QVariant(configsParameters.at(configName.DIRECTORY_MODE)));
    setCheckboxesFromFileSettings(configsParameters.at(configName.BROWSEABLE), browsableCheckBox3);
    setCheckboxesFromFileSettings(configsParameters.at(configName.WRITABLE), writablecheckBox3);
    setCheckboxesFromFileSettings(configsParameters.at(configName.GUEST_OK), guestOkCheckBox3);
}

void SambaConfig::bSave_onClicked()
{
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

void SambaConfig::bFileDialog_onAccepted(QString catalog)
{
    QString path = catalog.remove(0,7);
    pathTextField->setProperty("text",QVariant(path));
    vConfigs[1].configs.at(configName.PATH)=path;
}
