#include "SettingsPackages.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QProcess>
#include <QFile>
#include <QEventLoop>

SettingsPackages::SettingsPackages(QObject *parent) : QObject(parent)
{
}

bool SettingsPackages::checkIfServerIsConnected()
{
    QFile file("/etc/opkg/opkg.conf");

    bool status = false;
    QString serverAddress = "";

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical("Opkg congig file not exist");
        return false;
    }

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
    if(checkIfServerIsConnected())
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
    else
    {
        packageInfo->setProperty("text", QVariant("Server is not available"));
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
