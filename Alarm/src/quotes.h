#ifndef QUOTES_H
#define QUOTES_H

#include <QObject>

class Quotes : public QObject
{
    bool isSnooze;
    void closePriv();
    Q_OBJECT
public:
    explicit Quotes(QObject *parent = nullptr);
    Q_INVOKABLE void getQuote(QObject *quoteDialog);
    Q_INVOKABLE void saveAndClose(QString englishQuote, QString englishAuthor, QString polishQuote, QString polishAuthor);
    Q_INVOKABLE void close();
};

#endif // QUOTES_H
