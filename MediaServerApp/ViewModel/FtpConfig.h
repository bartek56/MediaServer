#ifndef FTPCONFIG_H
#define FTPCONFIG_H
#include <QtQuick>
#include <memory>
#include <algorithm>
#include "ConfigFile/FtpConfigFile.h"

class FtpConfig : public QObject
{
    Q_OBJECT
public:
    explicit FtpConfig(QObject *parent = nullptr);
    Q_INVOKABLE void setUsersComboBox(QObject *obj);
    Q_INVOKABLE void setPathTextField1(QObject *obj);
    Q_INVOKABLE void setPathTextField2(QObject *obj);
    Q_INVOKABLE void cbUser_onDisplayTextChanged(const QString text);
    Q_INVOKABLE void tfUser_onEditingFinished(const QString text);
    Q_INVOKABLE void bAddUser_onClicked(const QString userName, const QString password, const QString catalog);
    Q_INVOKABLE void bSave_onClicked();
    Q_INVOKABLE void bRemoveUser_onClick(const QString userName);
    Q_INVOKABLE void bUpdateUser_onClick(const QString userName, const QString path);
    Q_INVOKABLE void bFileDialog1_onAccepted(QString path);
    Q_INVOKABLE void bFileDialog2_onAccepted(QString path);
    Q_INVOKABLE void checkService(QObject *saveButton);

    Q_PROPERTY(bool fileValid READ isFileValid)

    bool isFileValid() const;

private:
    static constexpr char VSFTPD_USER_CONF_PATH[] = "/etc/vsftpd_user_conf/";
    static constexpr char FTP_SERVICE[] = "vsftpd.service";
    static constexpr char VSFTPD_USERS_CONFIG_FILE[] = "/etc/vsftpd/ftpd.passwd";
    bool serviceExist;
    bool configFilesExist;
    QObject *cbUsers;
    QObject *tfUser;
    QObject *tfPassword;
    QObject *tfPath1;
    QObject *tfPath2;
    FtpConfigFile editFile;
    QStringList users;
    std::vector<std::shared_ptr<FtpUser>> vNewUsersConfig;
    std::vector<std::shared_ptr<QString>> vRemoveUsersConfig;
    std::vector<std::shared_ptr<FtpUser>> vUpdateUsersConfig;
    QString getNewUserPath(const QString &userName);
    QString getUpdateUserPath(const QString &userName);
    void SaveUsers();
    void DeleteUsers();
    void UpdateUsers();
};

#endif// FTPCONFIG_H
