#ifndef SYSTEMDMANAGER_H
#define SYSTEMDMANAGER_H

#include <QString>
#include <QStringList>

class SystemdManager
{
public:
    static QString getUnitFileState(const QString &unitName);
    static QString activeState(const QString &unitName);

    static bool isUnitActive(const QString &unitName);
    static bool isUnitEnabled(const QString &unitName);
    static bool unitFileExists(const QString &unitName);

    static bool startUnit(const QString &unitName);
    static bool stopUnit(const QString &unitName);
    static bool restartUnit(const QString &unitName);
    static bool reload();

    static bool enableUnitFiles(const QStringList &unitNames, bool runtime, bool force);
    static bool disableUnitFiles(const QStringList &unitNames, bool runtime);
};

#endif // SYSTEMDMANAGER_H
