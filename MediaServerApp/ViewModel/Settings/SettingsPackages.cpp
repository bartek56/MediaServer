#include "SettingsPackages.h"
#include "ConfigFile/IConfigFile.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QProcess>
#include <QFile>
#include <QEventLoop>

SettingsPackages::SettingsPackages(QObject *parent) : QObject(parent)
{
    configIsValid = false;
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("opkg", QStringList() << "print-architecture");

    while(builder.waitForFinished())
        ;

    QString info = builder.readAll();
    if(info.isEmpty())
    {
        qCritical() << "opkg is not support";
        errorMessage = "OPKG is not supported on this system";
    }
    else
    {
        if(!QFile(OPKG_CONFIG_FILE).exists())
        {
            errorMessage = "OPKG config file not exists";
            qCritical("OPKG config file not exists");
        }
        else
        {
            const bool serverISRunning = checkIfServerIsConnected();
            if(!serverISRunning)
            {
                errorMessage = "OPKG server is not active";
                qCritical() << "OPKG server is not active";
            }
            else
            {
                configIsValid = true;
            }
        }
    }
}

bool SettingsPackages::configValid()
{
    return configIsValid;
}

QString SettingsPackages::getMessage()
{
    return errorMessage;
}

bool SettingsPackages::checkIfServerIsConnected()
{
    QFile file(OPKG_CONFIG_FILE);

    bool status = false;
    QString serverAddress = "";

    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        if(line.contains("all"))
        {
            auto line2 = line.split(' ');
            serverAddress = line2[2].trimmed();
        }
    }

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(serverAddress));
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    QEventLoop loop;
    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished,
            [reply, &loop, &status]()
            {
                auto response = reply->readAll();
                if(response.contains("Index of /all"))
                    status = true;
                loop.quit();
            });
    loop.exec();

    return status;
}


void SettingsPackages::bUpdate_onClicked(QObject *updateList, QObject *packageInfo)
{
    updateList->setProperty("editable", QVariant(true));

    // opkg update
    QProcess processListUpdate;
    processListUpdate.setProcessChannelMode(QProcess::MergedChannels);
    processListUpdate.start("opkg", QStringList() << "update");
    while(processListUpdate.waitForFinished())
        ;

    QProcess processListUpgradable;
    processListUpgradable.setProcessChannelMode(QProcess::MergedChannels);
    processListUpgradable.start("opkg", QStringList() << "list-upgradable");

    processListUpgradable.setReadChannel(QProcess::StandardOutput);
    QStringList packagesList;
    while(processListUpgradable.waitForFinished())
        ;
    while(processListUpgradable.canReadLine())
    {
        auto line = processListUpgradable.readLine();
        QString qStrLine = QString(line);
        auto packageName = qStrLine.section(" - ", 0, 0);
        packagesList.push_back(packageName);
    }

    //    packagesList.push_back("python-mutagen");

    updateList->setProperty("model", QVariant(packagesList));

    if(packagesList.count() > 0)
    {
        QProcess processPackageInfo;
        processPackageInfo.setProcessChannelMode(QProcess::MergedChannels);
        processPackageInfo.start("opkg", QStringList() << "info" << packagesList[0]);

        while(processPackageInfo.waitForFinished())
            ;

        QString packageInformation = processPackageInfo.readAll();
        packageInfo->setProperty("text", QVariant(packageInformation));
    }
    else
    {
        packageInfo->setProperty("text", QVariant("No packages"));
    }
}

void SettingsPackages::bUpgrade_onClicked(const QString packageName)
{
    QProcess upgradeProcess;
    upgradeProcess.setProcessChannelMode(QProcess::MergedChannels);
    upgradeProcess.start("opkg", QStringList() << "install" << packageName);
    while(upgradeProcess.waitForFinished(-1))
        ;
}

void SettingsPackages::bUpgradeAll_onClicked()
{
    QProcess upgradeProcess;
    upgradeProcess.setProcessChannelMode(QProcess::MergedChannels);
    upgradeProcess.start("opkg", QStringList() << "upgrade");
    while(upgradeProcess.waitForFinished(-1))
        ;
}

void SettingsPackages::cbPackage_onDisplayTextChanged(const QString packageName, QObject *packageSpecificationText)
{
    QProcess processPackageInfo;
    processPackageInfo.setProcessChannelMode(QProcess::MergedChannels);
    processPackageInfo.start("opkg", QStringList() << "info" << packageName);
    while(processPackageInfo.waitForFinished())
        ;

    QString packageInformation = processPackageInfo.readAll();
    packageSpecificationText->setProperty("text", QVariant(packageInformation));
}
