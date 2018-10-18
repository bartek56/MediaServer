#ifndef SAMBACONFIG_H
#define SAMBACONFIG_H

#include <QObject>
#include <memory>
#include <QSharedPointer>


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
    Q_INVOKABLE void bSave_onClicked(QString text);
    Q_INVOKABLE void openFile();

private:
    void setCheckboxesFromFileSettings(QString configsParameters, QSharedPointer<QObject> checkbox);

public slots:


};

#endif // SAMBACONFIG_H
