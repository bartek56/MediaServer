#ifndef SETTINGSPACKAGES_H
#define SETTINGSPACKAGES_H

#include <QObject>

class SettingsPackages : public QObject
{
private:

    Q_OBJECT
public:
    explicit SettingsPackages(QObject *parent = nullptr);

    Q_INVOKABLE void bUpdate_onClicked(QObject *updateList, QObject *packageInfo);
    Q_INVOKABLE void bUpgrade_onClicked(const QString packageName);
    Q_INVOKABLE void bUpgradeAll_onClicked();
    Q_INVOKABLE void cbPackage_onDisplayTextChanged(const QString packageName, QObject *packageSpecificationText);
};


#endif // SETTINGSPACKAGES_H
