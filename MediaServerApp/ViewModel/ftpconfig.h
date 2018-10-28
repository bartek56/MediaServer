#ifndef FTPCONFIG_H
#define FTPCONFIG_H
#include <QtQuick>
#include <memory>
#include <algorithm>
#include "editftpconfigfile.h"

class FtpConfig : public QObject
{
    Q_OBJECT

public:
    explicit FtpConfig(QObject *parent = nullptr);
    Q_INVOKABLE void setUsersComboBox(QObject* obj);
    Q_INVOKABLE void setPathTextField(QObject* obj);
    Q_INVOKABLE void cbUser_onDisplayTextChanged(const QString text);
    Q_INVOKABLE void tfUser_onEditingFinished(const QString text);
    Q_INVOKABLE void bAddUser_onClicked(const QString userName, const QString password, const QString catalog);
    Q_INVOKABLE void bSave_onClicked();


private:
    QObject* cbUsers;
    QObject* tfUser;
    QObject* tfPassword;
    QObject* tfPath;
    EditFtpConfigFile editFile;
    QStringList users;
    std::vector<std::shared_ptr<FtpUser>> vUserConfig;
    void SaveUsers();
    void CreateUserConfigFile();

};

#endif // FTPCONFIG_H
