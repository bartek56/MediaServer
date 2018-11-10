#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QProcess>


class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    Q_INVOKABLE void searchNetworks(QObject* obj);
    Q_INVOKABLE void updateStatus(QObject* obj);
    Q_INVOKABLE void connect(QString networkName, QString password);

signals:

public slots:

private:
    QObject* tInfo;
};

#endif // SETTINGS_H
