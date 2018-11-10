#include "settings.h"
#include <QDebug>
#include <QFile>

Settings::Settings(QObject *parent) : QObject(parent)
{

}

void Settings::updateStatus(QObject *obj)
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("iw dev wlan0 link");

    if (builder.waitForFinished())
    {
        QString info = builder.readAll();
        obj->setProperty("text",QVariant(info));
    }
}

void Settings::searchNetworks(QObject* obj)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("iw dev wlan0 scan");

    process.setReadChannel(QProcess::StandardOutput);
    QStringList networksList;
    while(process.waitForFinished());
    while (process.canReadLine())
    {
       auto line = process.readLine();
       std::string strLine(line);
       if (strLine.find("SSID")!=std::string::npos)
       {
           auto lineList = line.split(':');
           auto networkName = lineList[1];
           networkName=networkName.remove(0,1);
           networkName=networkName.remove(networkName.length()-1,1);
           std::string strNetworkName(networkName);
           QString qstrNetworkName = QString::fromStdString(strNetworkName);
           networksList.push_back(qstrNetworkName);
       }
    }

    obj->setProperty("model",QVariant(networksList));
}

void Settings::connect(QString networkName, QString password)
{
    QString filename="/etc/wpa_supplicant.conf";
    QFile file(filename);

    if (file.open(QIODevice::ReadWrite |  QIODevice::Append))
    {
        QTextStream stream(&file);
        stream << "network={" << "\n";
        stream << "ssid=\""<<networkName<<"\""<<"\n";
        stream << "psk=\""<<password<<"\""<<"\n";
        stream << "}" << "\n\n";
    }
    file.close();

    /*
    QString commend = "wpa_passphrase ";
    commend.push_back(networkName);
    commend.push_back(" ");
    commend.push_back(password);
    commend.push_back(" >> /etc/wpa_supplicant.conf");
    QProcess::execute(commend);
    */
}


