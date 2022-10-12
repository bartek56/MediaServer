#include "Quotes.h"
#include <QProcess>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QTextStream>

Quotes::Quotes(QObject *parent) : QObject(parent)
{
}

void Quotes::getQuote(QObject *quote)
{
    QProcess process;
    process.setProcessChannelMode(QProcess::SeparateChannels);
    process.setReadChannel(QProcess::StandardOutput);
    connect(&process, &QProcess::readyReadStandardOutput,
            [&process, &quote]()
            {
                int lineNumber = 0;
                while(process.canReadLine())
                {
                    if(lineNumber == 0)
                        quote->setProperty("quotePolish", QVariant(QString::fromLocal8Bit(process.readLine())));
                    else if(lineNumber == 1)
                        quote->setProperty("authorPolish", QVariant(QString::fromLocal8Bit(process.readLine())));
                    lineNumber++;
                }
            });

    process.start("python3", QStringList() << "/opt/quotes.py");
    process.waitForFinished();
}

void Quotes::save(const QString englishQuote, const QString englishAuthor, const QString polishQuote, const QString polishAuthor)
{
    QString path("/home/bbrzozowski/Documents/");
    QDir dir;

    if(!dir.exists(path))
        dir.mkpath(path);

    QDateTime dateNow = QDateTime::currentDateTime();
    auto dateNowString = dateNow.toString("yyyy/MM/dd hh:mm:ss");

    bool isNewQuote = false;
    QFile file(path + "quotes.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);

    QString previousQuotes = out.readAll();
    if(!previousQuotes.contains(englishQuote))
    {
        out << dateNowString << ": " << englishQuote << " - " << englishAuthor << ";";
        isNewQuote = true;
    }

    if(!previousQuotes.contains(polishQuote))
    {
        if(!isNewQuote)
            out << dateNowString << ": " << polishQuote << " - " << polishAuthor << ";";
        else
            out << polishQuote << " - " << polishAuthor << ";";
        isNewQuote = true;
    }

    if(isNewQuote)
        out << "\n";

    file.close();
}
