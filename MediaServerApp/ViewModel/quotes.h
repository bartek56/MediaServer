#ifndef QUOTES_H
#define QUOTES_H

#include <QObject>

class Quotes : public QObject
{
    Q_OBJECT
public:
    explicit Quotes(QObject *parent = nullptr);
    Q_INVOKABLE void getQuote(QObject *quoteDialog);
    Q_INVOKABLE void save(const QString englishQuote, const QString englishAuthor, const QString polishQuote, const QString polishAuthor);

signals:

};

#endif // QUOTES_H
