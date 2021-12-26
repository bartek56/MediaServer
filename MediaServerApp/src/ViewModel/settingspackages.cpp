#include "settingspackages.h"
#include <QDebug>
#include <QProcess>

SettingsPackages::SettingsPackages(QObject *parent): QObject(parent)
{

}


void SettingsPackages::bUpdate_onClicked(QObject *updateList, QObject *packageInfo)
{
    // opkg update

    QProcess processListUpgradable;
    processListUpgradable.setProcessChannelMode(QProcess::MergedChannels);
    processListUpgradable.start("bash", QStringList() << "-c" << "opkg list-upgradable");

    processListUpgradable.setReadChannel(QProcess::StandardOutput);
    QStringList packagesList;
    while(processListUpgradable.waitForFinished());
    while (processListUpgradable.canReadLine())
    {
       auto line = processListUpgradable.readLine();
       QString qStrLine = QString(line);
       auto packageName  = qStrLine.section(" - ",0,0);
       packagesList.push_back(packageName);
    }

//    packagesList.push_back("python-mutagen");

    updateList->setProperty("model",QVariant(packagesList));

    if(packagesList.count()>0)
    {
    QProcess processPackageInfo;
    processPackageInfo.setProcessChannelMode(QProcess::MergedChannels);
    processPackageInfo.start("bash", QStringList() << "-c" << "opkg info " + packagesList[0]);

    while(processPackageInfo.waitForFinished());

    QString packageInformation = processPackageInfo.readAll();
    packageInfo->setProperty("text",QVariant(packageInformation));
    }
    else {
        packageInfo->setProperty("text",QVariant("No packages"));
    }
}

void SettingsPackages::bUpgrade_onClicked(const QString packageName)
{
     QProcess upgradeProcess;
     upgradeProcess.setProcessChannelMode(QProcess::MergedChannels);
     upgradeProcess.start("opkg install " + packageName);
     while(upgradeProcess.waitForFinished(-1));
}

void SettingsPackages::bUpgradeAll_onClicked()
{
    QProcess upgradeProcess;
    upgradeProcess.setProcessChannelMode(QProcess::MergedChannels);
    upgradeProcess.start("opkg upgrade");
    while(upgradeProcess.waitForFinished(-1));
}

void SettingsPackages::cbPackage_onDisplayTextChanged(const QString packageName, QObject *packageSpecificationText)
{
    QProcess processPackageInfo;
    processPackageInfo.setProcessChannelMode(QProcess::MergedChannels);
    processPackageInfo.start("bash", QStringList() << "-c" << "opkg info " + packageName);
    while(processPackageInfo.waitForFinished());

    QString packageInformation = processPackageInfo.readAll();
    packageSpecificationText->setProperty("text",QVariant(packageInformation));
}
