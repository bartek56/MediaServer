#ifndef SAMBACONFIG_H
#define SAMBACONFIG_H

#include <QProcess>
#include <QSettings>
#include <memory>

struct ConfigName
{
    const QString WORKGROUP = "workgroup";
    const QString SERVER_STRING = "server string";
    const QString NETBIOS_NAME = "netbios name";
    const QString SECURITY = "security";
    const QString MAP_TO_GUEST = "map to guest";
    const QString BROWSEABLE = "browseable";
    const QString LOCAL_MASTER = "local master";
    const QString DOMAIN_MASTER = "domain master";
    const QString COMMENT = "comment";
    const QString PATH = "path";
    const QString CREATE_MODE = "create mode";
    const QString DIRECTORY_MODE = "directory mode";
    const QString WRITABLE = "writable";
    const QString GUEST_OK = "guest ok";
    const QString READ_ONLY = "read only";
    const QString FORCE_USER = "force user";
};

struct GlobalConfigName
{
    const QString BROWSE_ABLE = "GLOBAL/browseable";
    const QString DOMAIN_MASTER = "GLOBAL/domain master";
    const QString FORCE_USER = "GLOBAL/force user";
    const QString LOCAL_MASTER = "GLOBAL/local master";
    const QString MAP_TO_GUEST = "GLOBAL/map to guest";
    const QString NETBIOS_NAME = "GLOBAL/netbios name";
    const QString SECURITY = "GLOBAL/security";
    const QString SERVER_STRING = "GLOBAL/server string";
    const QString WORKGROUP = "GLOBAL/workgroup";
};

struct GlobalConfig
{
    QString workgroup;
    QString serverString;
    QString netbiosName;
    QString security;
    QString mapToGuest;
    QString forceUser;
    QString browseable;
    QString localMaster;
    QString domainMaster;
};

struct ShareConfig
{
    QString comment;
    QString path;
    QString createMode;
    QString directoryMode;
    QString browseable;
    QString writable;
    QString guestOk;
    QString readOnly;
};

struct SambaShareObjects
{
    QObject *nameTextField;
    QObject *pathTextField;
    QObject *createModeTextField;
    QObject *directoryModeTextField;
    QObject *browsableCheckBox;
    QObject *writablecheckBox;
    QObject *guestOkCheckBox;
    QObject *readOnlyCheckBox;
    QObject *enabledCheckBox;
};

class SambaConfig : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool fileValid READ isFileValid)

public:
    QObject *stackLayout;

    QObject *workGroupTextField;
    QObject *serverStringTextField;
    QObject *netBiosTextField;
    QObject *globalBrowsableCheckBox;
    QObject *localMastercheckBox;
    QObject *domainMasterCheckBox;
    QObject *securityComboBox;
    QObject *mapToGuestComboBox;

    explicit SambaConfig(QObject *parent = nullptr);
    bool isFileValid() const;

    Q_INVOKABLE void setStackLayout(QObject *obj);

    Q_INVOKABLE void setWorkGroupTextField(QObject *obj);
    Q_INVOKABLE void setServerStringTextField(QObject *obj);
    Q_INVOKABLE void setNetBiosTextField(QObject *obj);
    Q_INVOKABLE void setGlobalBrowsableCheckBox(QObject *obj);
    Q_INVOKABLE void setLocalMasterCheckBox(QObject *obj);
    Q_INVOKABLE void setDomainMasterCheckBox(QObject *obj);
    Q_INVOKABLE void setSecurityComboBox(QObject *obj);
    Q_INVOKABLE void setMapToGuestComboBox(QObject *obj);

    Q_INVOKABLE void setCommentTextField(QObject *obj);
    Q_INVOKABLE void setPathTextField(QObject *obj);
    Q_INVOKABLE void setCreateModeTextField(QObject *obj);
    Q_INVOKABLE void setDirectoryModeTextField(QObject *obj);
    Q_INVOKABLE void setBrowsableCheckBox(QObject *obj);
    Q_INVOKABLE void setWritablecheckBox(QObject *obj);
    Q_INVOKABLE void setGuestOkCheckBox(QObject *obj);
    Q_INVOKABLE void setReadOnlyCheckBox(QObject *obj);

    Q_INVOKABLE void setCommentTextField1(QObject *obj);
    Q_INVOKABLE void setPathTextField1(QObject *obj);
    Q_INVOKABLE void setCreateModeTextField1(QObject *obj);
    Q_INVOKABLE void setDirectoryModeTextField1(QObject *obj);
    Q_INVOKABLE void setBrowsableCheckBox1(QObject *obj);
    Q_INVOKABLE void setWritablecheckBox1(QObject *obj);
    Q_INVOKABLE void setGuestOkCheckBox1(QObject *obj);
    Q_INVOKABLE void setReadOnlyCheckBox1(QObject *obj);
    Q_INVOKABLE void setEnabled1(QObject *obj);

    Q_INVOKABLE void setCommentTextField2(QObject *obj);
    Q_INVOKABLE void setPathTextField2(QObject *obj);
    Q_INVOKABLE void setCreateModeTextField2(QObject *obj);
    Q_INVOKABLE void setDirectoryModeTextField2(QObject *obj);
    Q_INVOKABLE void setBrowsableCheckBox2(QObject *obj);
    Q_INVOKABLE void setWritablecheckBox2(QObject *obj);
    Q_INVOKABLE void setGuestOkCheckBox2(QObject *obj);
    Q_INVOKABLE void setReadOnlyCheckBox2(QObject *obj);
    Q_INVOKABLE void setEnabled2(QObject *obj);

    Q_INVOKABLE void setCommentTextField3(QObject *obj);
    Q_INVOKABLE void setPathTextField3(QObject *obj);
    Q_INVOKABLE void setCreateModeTextField3(QObject *obj);
    Q_INVOKABLE void setDirectoryModeTextField3(QObject *obj);
    Q_INVOKABLE void setBrowsableCheckBox3(QObject *obj);
    Q_INVOKABLE void setWritablecheckBox3(QObject *obj);
    Q_INVOKABLE void setGuestOkCheckBox3(QObject *obj);
    Q_INVOKABLE void setReadOnlyCheckBox3(QObject *obj);
    Q_INVOKABLE void setEnabled3(QObject *obj);

    Q_INVOKABLE void bSave_onClicked();

    Q_INVOKABLE void tfNetbiosName_onEditingFinished(QString text);
    Q_INVOKABLE void tfWorkgroup_onEditingFinished(QString text);
    Q_INVOKABLE void tfServerString_onEditingFinished(QString text);

    Q_INVOKABLE void cbMapToGuest_onDisplayTextChanged(QString text);
    Q_INVOKABLE void cbSecurity_onDisplayTextChanged(QString text);
    Q_INVOKABLE void cbLocalMaster_onClicked(bool checked);
    Q_INVOKABLE void cbDomainMaster_onClicked(bool checked);
    Q_INVOKABLE void cbGlobalBrowseable_onClicked(bool checked);

    Q_INVOKABLE void tfName_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable_onClicked(bool checked);
    Q_INVOKABLE void chbWritable_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly_onClicked(bool checked);
    Q_INVOKABLE void bFileDialog_onAccepted(QString catalog);

    Q_INVOKABLE void tfName1_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath1_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode1_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode1_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable1_onClicked(bool checked);
    Q_INVOKABLE void chbWritable1_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk1_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly1_onClicked(bool checked);
    Q_INVOKABLE void bFileDialog1_onAccepted(QString catalog);

    Q_INVOKABLE void tfName2_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath2_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode2_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode2_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable2_onClicked(bool checked);
    Q_INVOKABLE void chbWritable2_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk2_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly2_onClicked(bool checked);
    Q_INVOKABLE void bFileDialog2_onAccepted(QString catalog);

    Q_INVOKABLE void tfName3_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath3_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode3_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode3_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable3_onClicked(bool checked);
    Q_INVOKABLE void chbWritable3_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk3_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly3_onClicked(bool checked);
    Q_INVOKABLE void bFileDialog3_onAccepted(QString catalog);

    Q_INVOKABLE void loadAllConfigs(QObject *isEnabled);

private:
    bool isConfigFile;
    bool systemdSupport;
    const QString SMB_SERVICE = "smb.service";
    const QString NMB_SERVICE = "nmb.service";

    ConfigName configName;
    GlobalConfigName globalConfigName;

    GlobalConfig globalConfig;
    ShareConfig shareConfig1;
    ShareConfig shareConfig2;
    ShareConfig shareConfig3;
    ShareConfig shareConfig4;

    SambaShareObjects sambaShare1;
    SambaShareObjects sambaShare2;
    SambaShareObjects sambaShare3;
    SambaShareObjects sambaShare4;


    unsigned int indexOfExternalDiskConfiguration(QString diskName);
    unsigned int indexOfExternalDiskConfigurationByName(QString name);
    void setCheckboxesFromFileSettings(QString configsParameters, QObject *checkbox);
    void setSettingFromCheckboxes(QString &configName, bool checked);

    void showGlobalConfigs();
    void showLocalConfigs();

    void loadConfigsForShare(ShareConfig &shareConfig, const QSettings &settings, const QString &shareName);

    void setDefaultConfigsForShare(ShareConfig &shareConfig, const QString &name, const QString &path);
    void saveShare(QSettings &settings, const ShareConfig &shareConfig);

    void showConfigsForExternalDisk(const SambaShareObjects &sambaConfig, const ShareConfig &shareConfig);
    bool isServiceActive();

public slots:
};

#endif// SAMBACONFIG_H
