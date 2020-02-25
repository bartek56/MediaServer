#include "bluetoothctl.h"
#include <QDebug>
#include <QTextEdit>

Bluetoothctl::Bluetoothctl(QObject *parent) : QObject (parent)
{
    process = new QProcess();
    process->setProcessChannelMode(QProcess::SeparateChannels);
    process->setReadChannel(QProcess::StandardOutput);
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));

    process->start("bluetoothctl");
    process->waitForStarted();
    process->write(QByteArray("agent on \n"));
    process->write(QByteArray("default-agent \n"));
    process->write(QByteArray("discoverable on \n"));
}

void Bluetoothctl::readOutput()
{
        auto result = process->readAll();
        //result.replace("\x1B[0;94m","");
        //result.replace("\x1B[0;93m","");
        //result.replace("\x1B[0;91m","");
        //result.replace("\x1B[0m","");
        //result.replace('\"',"");
        QString test = QString(result);
        test.remove("\x1B[0;94m");
        test.remove("\x1B[0;93m");
        test.remove("\x1B[0;91m");
        test.remove("\u001B[0;92m");
        test.remove("\r                        \r");
        test.remove("\r                     \r");
        test.remove("\x1B[0m");
        //test.remove(QRegExp("\\s+"));
        //"[NEW] Device F4:60:E2:F1:D9:09 Xiaomi"
        QString newMacNumber;
        QString newDeviceName;

        auto resultLines = test.split('\n');
        for(auto i : resultLines)
        {
            qDebug() << i;

            if(i.contains("#") && (!i.contains("bluetooth") && !i.contains("NEW")))
            {
                // get text only in  [ ]
                auto start = i.indexOf('[');
                start++;
                auto end = i.indexOf(']');
                for(int k=start; k<end; k++)
                {
                    newDeviceName.push_back(i[k]);
                }
                if(deviceName != newDeviceName)
                    deviceName=newDeviceName;
            }
            if(i.contains("Device"))
            {
                auto start = i.indexOf("Device");
                start+=7;
                int end = start + 17;
                for(int k=start; k<end; k++)
                {
                    newMacNumber.push_back(i[k]);
                }
                if(macNumber != newMacNumber)
                    macNumber = newMacNumber;
            }
        }


        if(result.contains("(yes/no)"))
        {

            QString infoText = "Do You want pair with \"" + deviceName +"\" device ("+macNumber+") ?";
            messageDialog->setProperty("text", QVariant(infoText));
            messageDialog->setProperty("visible", QVariant(true));
        }

        if(result.contains("Request canceled"))
        {
            messageDialog->setProperty("visible", QVariant(false));
        }
}

void Bluetoothctl::pair()
{
    process->write(QByteArray("yes\n"));
}

void Bluetoothctl::trust()
{
    process->write(QByteArray("yes\n"));
    QString trust = "trust " + macNumber+ " \n";
    process->write(trust.toUtf8());
}

void Bluetoothctl::cancel()
{
    process->write(QByteArray("no\n"));
    messageDialog->setProperty("visible", QVariant(false));
}

void Bluetoothctl::setMessageDialog(QObject *messageDialog)
{
    this->messageDialog = messageDialog;
}

Bluetoothctl::~Bluetoothctl()
{
    process->kill();
}
