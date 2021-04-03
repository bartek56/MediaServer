#include "quotes.h"
#include <QProcess>
#include <QDebug>

Quotes::Quotes(QObject *parent) : QObject(parent)
{
}

void Quotes::getQuote(QObject *quote, QObject *artist)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::SeparateChannels);
    process.setReadChannel(QProcess::StandardOutput);
    connect(&process, &QProcess::readyReadStandardOutput, [&process, &quote, &artist](){
        int lineNumber=0;
        while(process.canReadLine())
        {
            if(lineNumber==0)
                quote->setProperty("text", QVariant(QString::fromLocal8Bit(process.readLine())));
            else if(lineNumber==1)
                artist->setProperty("text", QVariant(QString::fromLocal8Bit(process.readLine())));
            lineNumber++;
        }
    });

    process.start("python3 /opt/quotes.py");
    process.waitForFinished();
}
