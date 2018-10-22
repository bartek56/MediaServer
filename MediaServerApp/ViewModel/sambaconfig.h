#ifndef SAMBACONFIG_H
#define SAMBACONFIG_H

#include <QObject>
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
  };

class SambaConfig : public QObject
{
    Q_OBJECT
public:
    QSharedPointer<QObject> workGroupTextField;
    QSharedPointer<QObject> serverStringTextField;
    QSharedPointer<QObject> netBiosTextField;
    QSharedPointer<QObject> browsableCheckBox;
    QSharedPointer<QObject> localMastercheckBox;
    QSharedPointer<QObject> domainMasterCheckBox;
    QSharedPointer<QObject> securityComboBox;
    QSharedPointer<QObject> mapToGuestComboBox;

    explicit SambaConfig(QObject *parent = nullptr);

    Q_INVOKABLE void setWorkGroupTextField(QObject* obj);
    Q_INVOKABLE void setServerStringTextField(QObject* obj);
    Q_INVOKABLE void setNetBiosTextField(QObject* obj);
    Q_INVOKABLE void setBrowsableCheckBox(QObject* obj);
    Q_INVOKABLE void setLocalMastercheckBox(QObject* obj);
    Q_INVOKABLE void setDomainMasterCheckBox(QObject* obj);
    Q_INVOKABLE void setSecurityComboBox(QObject* obj);
    Q_INVOKABLE void setMapToGuestComboBox(QObject* obj);
    Q_INVOKABLE void bSave_onClicked();
    Q_INVOKABLE void tfNetbiosName_onEditingFinished(QString text);
    Q_INVOKABLE void tfWorkgroup_onEditingFinished(QString text);
    Q_INVOKABLE void tfServerString_onEditingFinished(QString text);
    Q_INVOKABLE void cbMapToGuest_onDisplayTextChanged(QString text);
    Q_INVOKABLE void cbSecurity_onDisplayTextChanged(QString text);
    Q_INVOKABLE void cbLocalMaster_onClicked(bool checked);
    Q_INVOKABLE void cbDomainMaster_onClicked(bool checked);
    Q_INVOKABLE void cbBrowseable_onClicked(bool checked);
    Q_INVOKABLE void openFile();

private:
    EditFile editFile;
    std::vector<ConfigsName> vConfigs;
    ConfigName configName;
    void setCheckboxesFromFileSettings(QString configsParameters, QSharedPointer<QObject> checkbox);
    void setSettingFromCheckboxes(QString configName, bool configsParameters);
    void loadConfigs();

public slots:

};


#endif // SAMBACONFIG_H
