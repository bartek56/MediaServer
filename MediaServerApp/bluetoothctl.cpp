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
    process->write(QByteArray("discoverable on \n"));
    process->write(QByteArray("agent on \n"));
    process->write(QByteArray("default-agent \n"));
}

void Bluetoothctl::readOutput()
{
        auto result = process->readAll();
        if(result.contains("(yes/no)"))
        {
            messageDialog->setProperty("visible",QVariant(true));
        }

        if(result.contains("Request canceled"))
        {
            messageDialog->setProperty("visible",QVariant(false));
        }
}

void Bluetoothctl::pair()
{
    process->write(QByteArray("yes\n"));
}

void Bluetoothctl::setMessageDialog(QObject *messageDialog)
{
    this->messageDialog = messageDialog;
}

Bluetoothctl::~Bluetoothctl()
{
    process->kill();
}
