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
        QString resultQString = QString(result);
        resultQString.remove("\x1B[0;94m");
        resultQString.remove("\x1B[0;93m");
        resultQString.remove("\x1B[0;91m");
        resultQString.remove("\u001B[0;92m");
        resultQString.remove("\x1B[0m");
        resultQString.remove("\r                        \r");
        resultQString.remove("\r                     \r");

        QString newMacNumber;
        QString newDeviceName;

        auto resultLines = resultQString.split('\n');
        for(auto line : resultLines)
        {
            if(line.contains("#") && (!line.contains("bluetooth") && !line.contains("NEW")))
            {
                auto start = line.indexOf('[');
                start++;
                auto end = line.indexOf(']');
                for(int k=start; k<end; k++)
                {
                    newDeviceName.push_back(line[k]);
                }
                if(deviceName != newDeviceName)
                    deviceName=newDeviceName;
            }
            if(line.contains("Device"))
            {
                auto start = line.indexOf("Device");
                start+=7;
                int end = start + 17;
                for(int k=start; k<end; k++)
                {
                    newMacNumber.push_back(line[k]);
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
    QString trust = "trust " + macNumber+ "\n";
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
