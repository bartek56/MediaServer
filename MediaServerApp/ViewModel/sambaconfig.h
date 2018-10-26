#ifndef SAMBACONFIG_H
#define SAMBACONFIG_H

#include <QProcess>
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
    QObject* stackLayout;

    QObject* workGroupTextField;
    QObject* serverStringTextField;
    QObject* netBiosTextField;
    QObject* globalBrowsableCheckBox;
    QObject* localMastercheckBox;
    QObject* domainMasterCheckBox;
    QObject* securityComboBox;
    QObject* mapToGuestComboBox;

    QObject* nameTextField;
    QObject* pathTextField;
    QObject* createModeTextField;
    QObject* directoryModeTextField;
    QObject* browsableCheckBox;
    QObject* writablecheckBox;
    QObject* guestOkCheckBox;
    QObject* readOnlyCheckBox;


    QObject* externalDiskTabButton1;

    QObject* nameTextField1;
    QObject* pathTextField1;
    QObject* createModeTextField1;
    QObject* directoryModeTextField1;
    QObject* browsableCheckBox1;
    QObject* writablecheckBox1;
    QObject* guestOkCheckBox1;
    QObject* readOnlyCheckBox1;

    QObject* externalDiskTabButton2;

    QObject* nameTextField2;
    QObject* pathTextField2;
    QObject* createModeTextField2;
    QObject* directoryModeTextField2;
    QObject* browsableCheckBox2;
    QObject* writablecheckBox2;
    QObject* guestOkCheckBox2;
    QObject* readOnlyCheckBox2;

    QObject* externalDiskTabButton3;

    QObject* nameTextField3;
    QObject* pathTextField3;
    QObject* createModeTextField3;
    QObject* directoryModeTextField3;
    QObject* browsableCheckBox3;
    QObject* writablecheckBox3;
    QObject* guestOkCheckBox3;
    QObject* readOnlyCheckBox3;

    explicit SambaConfig(QObject *parent = nullptr);

    Q_INVOKABLE void setStackLayout(QObject* obj);

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

    Q_INVOKABLE void setExternalDiskTabButton1(QObject* obj);
    Q_INVOKABLE void setCommentTextField1(QObject* obj);
    Q_INVOKABLE void setPathTextField1(QObject* obj);
    Q_INVOKABLE void setCreateModeTextField1(QObject* obj);
    Q_INVOKABLE void setDirectoryModeTextField1(QObject* obj);
    Q_INVOKABLE void setBrowsableCheckBox1(QObject* obj);
    Q_INVOKABLE void setWritablecheckBox1(QObject* obj);
    Q_INVOKABLE void setGuestOkCheckBox1(QObject* obj);
    Q_INVOKABLE void setReadOnlyCheckBox1(QObject* obj);

    Q_INVOKABLE void setExternalDiskTabButton2(QObject* obj);
    Q_INVOKABLE void setCommentTextField2(QObject* obj);
    Q_INVOKABLE void setPathTextField2(QObject* obj);
    Q_INVOKABLE void setCreateModeTextField2(QObject* obj);
    Q_INVOKABLE void setDirectoryModeTextField2(QObject* obj);
    Q_INVOKABLE void setBrowsableCheckBox2(QObject* obj);
    Q_INVOKABLE void setWritablecheckBox2(QObject* obj);
    Q_INVOKABLE void setGuestOkCheckBox2(QObject* obj);
    Q_INVOKABLE void setReadOnlyCheckBox2(QObject* obj);

    Q_INVOKABLE void setExternalDiskTabButton3(QObject* obj);
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

    Q_INVOKABLE void tfName_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable_onClicked(bool checked);
    Q_INVOKABLE void chbWritable_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly_onClicked(bool checked);

    Q_INVOKABLE void tfName1_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath1_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode1_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode1_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable1_onClicked(bool checked);
    Q_INVOKABLE void chbWritable1_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk1_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly1_onClicked(bool checked);
    Q_INVOKABLE void bUmount1_onClicked();

    Q_INVOKABLE void tfName2_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath2_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode2_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode2_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable2_onClicked(bool checked);
    Q_INVOKABLE void chbWritable2_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk2_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly2_onClicked(bool checked);
    Q_INVOKABLE void bUmount2_onClicked();

    Q_INVOKABLE void tfName3_onEditingFinished(QString text);
    Q_INVOKABLE void tfPath3_onEditingFinished(QString text);
    Q_INVOKABLE void tfCreateMode3_onEditingFinished(QString text);
    Q_INVOKABLE void tfDirectoryMode3_onEditingFinished(QString text);
    Q_INVOKABLE void chbBrowseable3_onClicked(bool checked);
    Q_INVOKABLE void chbWritable3_onClicked(bool checked);
    Q_INVOKABLE void chbGuestOk3_onClicked(bool checked);
    Q_INVOKABLE void chbReadOnly3_onClicked(bool checked);
    Q_INVOKABLE void bUmount3_onClicked();

    Q_INVOKABLE void openFile();
    Q_INVOKABLE void checkExternalDisks();
    Q_INVOKABLE void mountExternalDisks();

private:
    EditFile editFile;
    std::vector<ConfigsName> vConfigs;
    ConfigName configName;
    bool externalDisk1IsConnected;
    bool externalDisk2IsConnected;
    bool externalDisk3IsConnected;
    bool externalDisk1IsMounted;
    bool externalDisk2IsMounted;
    bool externalDisk3IsMounted;

    void removeConfig(QString const configName);
    unsigned int indexOfExternalDiskConfiguration(QString diskName);
    void setCheckboxesFromFileSettings(QString configsParameters, QObject* checkbox);
    void setSettingFromCheckboxes(unsigned long row, QString configName, bool configsParameters);
    void loadGlobalConfigs();
    void loadLocalConfigs();
    void loadExternalDisk1Configs();
    void loadExternalDisk2Configs();
    void loadExternalDisk3Configs();
    void checkingIfDisksAreMounted();

public slots:

};

#endif // SAMBACONFIG_H
