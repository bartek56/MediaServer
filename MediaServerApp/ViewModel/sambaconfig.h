#ifndef SAMBACONFIG_H
#define SAMBACONFIG_H


#include <memory>
#include <QSharedPointer>
#include "editfile.h"

struct ConfigName {
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
  };

class SambaConfig : public QObject
{
    Q_OBJECT
public:
    QSharedPointer<QObject> workGroupTextField;
    QSharedPointer<QObject> serverStringTextField;
    QSharedPointer<QObject> netBiosTextField;
    QSharedPointer<QObject> globalBrowsableCheckBox;
    QSharedPointer<QObject> localMastercheckBox;
    QSharedPointer<QObject> domainMasterCheckBox;
    QSharedPointer<QObject> securityComboBox;
    QSharedPointer<QObject> mapToGuestComboBox;

    QSharedPointer<QObject> commentTextField;
    QSharedPointer<QObject> pathTextField;
    QSharedPointer<QObject> createModeTextField;
    QSharedPointer<QObject> directoryModeTextField;
    QSharedPointer<QObject> browsableCheckBox;
    QSharedPointer<QObject> writablecheckBox;
    QSharedPointer<QObject> guestOkCheckBox;
    QSharedPointer<QObject> readOnlyCheckBox;


    QObject* externalDeviceTabButton1;

    QSharedPointer<QObject> commentTextField1;
    QSharedPointer<QObject> pathTextField1;
    QSharedPointer<QObject> createModeTextField1;
    QSharedPointer<QObject> directoryModeTextField1;
    QSharedPointer<QObject> browsableCheckBox1;
    QSharedPointer<QObject> writablecheckBox1;
    QSharedPointer<QObject> guestOkCheckBox1;
    QSharedPointer<QObject> readOnlyCheckBox1;

    QSharedPointer<QObject> externalDeviceTabButton2;

    QSharedPointer<QObject> commentTextField2;
    QSharedPointer<QObject> pathTextField2;
    QSharedPointer<QObject> createModeTextField2;
    QSharedPointer<QObject> directoryModeTextField2;
    QSharedPointer<QObject> browsableCheckBox2;
    QSharedPointer<QObject> writablecheckBox2;
    QSharedPointer<QObject> guestOkCheckBox2;
    QSharedPointer<QObject> readOnlyCheckBox2;

    QSharedPointer<QObject> externalDeviceTabButton3;

    QSharedPointer<QObject> commentTextField3;
    QSharedPointer<QObject> pathTextField3;
    QSharedPointer<QObject> createModeTextField3;
    QSharedPointer<QObject> directoryModeTextField3;
    QSharedPointer<QObject> browsableCheckBox3;
    QSharedPointer<QObject> writablecheckBox3;
    QSharedPointer<QObject> guestOkCheckBox3;
    QSharedPointer<QObject> readOnlyCheckBox3;


    explicit SambaConfig(QObject *parent = nullptr);

    Q_INVOKABLE void setWorkGroupTextField(QObject* obj);
    Q_INVOKABLE void setServerStringTextField(QObject* obj);
    Q_INVOKABLE void setNetBiosTextField(QObject* obj);
    Q_INVOKABLE void setGlobalBrowsableCheckBox(QObject* obj);
    Q_INVOKABLE void setLocalMasterCheckBox(QObject* obj);
    Q_INVOKABLE void setDomainMasterCheckBox(QObject* obj);
    Q_INVOKABLE void setSecurityComboBox(QObject* obj);
    Q_INVOKABLE void setMapToGuestComboBox(QObject* obj);


    Q_INVOKABLE void setCommentTextField(QObject* obj);
    Q_INVOKABLE void setPathTextField(QObject* obj);
    Q_INVOKABLE void setCreateModeTextField(QObject* obj);
    Q_INVOKABLE void setDirectoryModeTextField(QObject* obj);
    Q_INVOKABLE void setBrowsableCheckBox(QObject* obj);
    Q_INVOKABLE void setWritablecheckBox(QObject* obj);
    Q_INVOKABLE void setGuestOkCheckBox(QObject* obj);
    Q_INVOKABLE void setReadOnlyCheckBox(QObject* obj);

    Q_INVOKABLE void setExternalDeviceTabButton1(QObject* obj);

    Q_INVOKABLE void setCommentTextField1(QObject* obj);
    Q_INVOKABLE void setPathTextField1(QObject* obj);
    Q_INVOKABLE void setCreateModeTextField1(QObject* obj);
    Q_INVOKABLE void setDirectoryModeTextField1(QObject* obj);
    Q_INVOKABLE void setBrowsableCheckBox1(QObject* obj);
    Q_INVOKABLE void setWritablecheckBox1(QObject* obj);
    Q_INVOKABLE void setGuestOkCheckBox1(QObject* obj);
    Q_INVOKABLE void setReadOnlyCheckBox1(QObject* obj);

    Q_INVOKABLE void setExternalDeviceTabButton2(QObject* obj);

    Q_INVOKABLE void setCommentTextField2(QObject* obj);
    Q_INVOKABLE void setPathTextField2(QObject* obj);
    Q_INVOKABLE void setCreateModeTextField2(QObject* obj);
    Q_INVOKABLE void setDirectoryModeTextField2(QObject* obj);
    Q_INVOKABLE void setBrowsableCheckBox2(QObject* obj);
    Q_INVOKABLE void setWritablecheckBox2(QObject* obj);
    Q_INVOKABLE void setGuestOkCheckBox2(QObject* obj);
    Q_INVOKABLE void setReadOnlyCheckBox2(QObject* obj);

    Q_INVOKABLE void setExternalDeviceTabButton3(QObject* obj);

    Q_INVOKABLE void setCommentTextField3(QObject* obj);
    Q_INVOKABLE void setPathTextField3(QObject* obj);
    Q_INVOKABLE void setCreateModeTextField3(QObject* obj);
    Q_INVOKABLE void setDirectoryModeTextField3(QObject* obj);
    Q_INVOKABLE void setBrowsableCheckBox3(QObject* obj);
    Q_INVOKABLE void setWritablecheckBox3(QObject* obj);
    Q_INVOKABLE void setGuestOkCheckBox3(QObject* obj);
    Q_INVOKABLE void setReadOnlyCheckBox3(QObject* obj);


    Q_INVOKABLE void bSave_onClicked();

    Q_INVOKABLE void tfNetbiosName_onEditingFinished(QString text);
    Q_INVOKABLE void tfWorkgroup_onEditingFinished(QString text);
    Q_INVOKABLE void tfServerString_onEditingFinished(QString text);

    Q_INVOKABLE void cbMapToGuest_onDisplayTextChanged(QString text);
    Q_INVOKABLE void cbSecurity_onDisplayTextChanged(QString text);
    Q_INVOKABLE void cbLocalMaster_onClicked(bool checked);
    Q_INVOKABLE void cbDomainMaster_onClicked(bool checked);
    Q_INVOKABLE void cbGlobalBrowseable_onClicked(bool checked);

    Q_INVOKABLE void tfComment_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable_onClicked(bool checked);
    Q_INVOKABLE void chbWritable_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly_onClicked(bool checked);

    Q_INVOKABLE void openFile();
    Q_INVOKABLE void checkExternalDevices();

private:
    EditFile editFile;
    std::vector<ConfigsName> vConfigs;
    ConfigName configName;
    void setCheckboxesFromFileSettings(QString configsParameters, QSharedPointer<QObject> checkbox);
    void setSettingFromCheckboxes(unsigned long row,QString configName, bool configsParameters);
    void loadGlobalConfigs();
    void loadLocalConfigs();
    void loadExternalDevice1Configs();
    int countExternalDevice;

public slots:

};


#endif // SAMBACONFIG_H
