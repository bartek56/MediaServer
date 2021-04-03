#ifndef QUOTES_H
#define QUOTES_H

#include <QObject>

class Quotes : public QObject
{
    Q_OBJECT
public:
    explicit Quotes(QObject *parent = nullptr);
    Q_INVOKABLE void getQuote(QObject *quote, QObject *author);

signals:

};

#endif // QUOTES_H
