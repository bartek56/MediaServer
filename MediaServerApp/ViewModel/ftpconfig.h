#ifndef FTPCONFIG_H
#define FTPCONFIG_H
#include <QtQuick>

class FtpConfig : public QObject
{
    Q_OBJECT

public:
    explicit FtpConfig(QObject *parent = nullptr);

    QObject* usersCombobox;
    Q_INVOKABLE void setUsersComboBox(QObject* obj);
    Q_INVOKABLE void cbUser_onDisplayTextChanged(QString text);

};

#endif // FTPCONFIG_H
