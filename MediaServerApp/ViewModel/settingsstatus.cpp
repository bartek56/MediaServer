#include "settings.h"

#include <QDebug>
#include <QFile>
#include <map>

Settings::Settings(QObject *parent) : QObject(parent)
{

}

void Settings::updateNetworkStatus(QObject *obj)
{
    QProcess builder;
    builder.setProcessChannelMode(QProcess::MergedChannels);
    builder.start("networkctl status");

    if (builder.waitForFinished())
    {
        QString info = builder.readAll();
        obj->setProperty("text",QVariant(info));
    }
}
