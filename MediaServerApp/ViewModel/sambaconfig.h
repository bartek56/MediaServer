#ifndef SAMBACONFIG_H
#define SAMBACONFIG_H

#include <QObject>
#include <memory>
#include <QSharedPointer>


class SambaConfig : public QObject
{
    Q_OBJECT
public:
    //QObject *workGroupTextField;

    QSharedPointer<QObject> workGroupTextField;
    QSharedPointer<QObject> serverStringTextField;
    QSharedPointer<QObject> netBiosTextField;
    /*
    std::unique_ptr<QObject> browsableCheckBox;
    std::unique_ptr<QObject> localMastercheckBox;
    std::unique_ptr<QObject> domainMasterCheckBox;
    std::unique_ptr<QObject> securityComboBox;
    std::unique_ptr<QObject> mapToGuestComboBox;
    */
    explicit SambaConfig(QObject *parent = nullptr);

    Q_INVOKABLE void setWorkGroupTextField(QObject* obj);
    Q_INVOKABLE void setServerStringTextField(QObject* obj);
    Q_INVOKABLE void setNetBiosTextField(QObject* obj);
    /*
    Q_INVOKABLE void setBrowsableCheckBox(std::unique_ptr<QObject> obj);
    Q_INVOKABLE void setLocalMastercheckBox(std::unique_ptr<QObject> obj);
    Q_INVOKABLE void setDomainMasterCheckBox(std::unique_ptr<QObject> obj);
    Q_INVOKABLE void setSecurityComboBox(std::unique_ptr<QObject> obj);
    Q_INVOKABLE void setMapToGuestComboBox(std::unique_ptr<QObject> obj);
*/
    Q_INVOKABLE void bSave_onClicked(QString text);
    Q_INVOKABLE void openFile();

public slots:


};

#endif // SAMBACONFIG_H
