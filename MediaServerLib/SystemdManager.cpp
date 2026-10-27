#include "SystemdManager.h"

#include <QDBusConnection>
#include <QDBusError>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusObjectPath>
#include <QDBusReply>
#include <QDBusVariant>
#include <QDebug>
#include <QVariant>

namespace
{
constexpr auto SYSTEMD_BUS_NAME = "org.freedesktop.systemd1";
constexpr auto SYSTEMD_OBJECT_PATH = "/org/freedesktop/systemd1";
constexpr auto SYSTEMD_MANAGER_INTERFACE = "org.freedesktop.systemd1.Manager";
constexpr auto SYSTEMD_UNIT_INTERFACE = "org.freedesktop.systemd1.Unit";
constexpr auto DBUS_PROPERTIES_INTERFACE = "org.freedesktop.DBus.Properties";
constexpr auto REPLACE_JOB_MODE = "replace";

QDBusInterface managerInterface()
{
    return QDBusInterface(SYSTEMD_BUS_NAME,
                          SYSTEMD_OBJECT_PATH,
                          SYSTEMD_MANAGER_INTERFACE,
                          QDBusConnection::systemBus());
}

bool isValidManager(QDBusInterface &manager, const QString &operation)
{
    if(manager.isValid())
        return true;

    qWarning() << "Cannot access systemd over D-Bus for" << operation << ":" << manager.lastError().message();
    return false;
}

void logReplyError(const QString &operation, const QDBusError &error)
{
    qWarning() << "systemd D-Bus operation failed:" << operation << error.name() << error.message();
}

bool isSuccessful(const QDBusMessage &reply, const QString &operation)
{
    if(reply.type() == QDBusMessage::ReplyMessage)
        return true;

    if(reply.type() == QDBusMessage::ErrorMessage)
        qWarning() << "systemd D-Bus operation failed:" << operation << reply.errorName() << reply.errorMessage();
    else
        qWarning() << "systemd D-Bus operation returned an invalid reply:" << operation;

    return false;
}

QDBusObjectPath unitObjectPath(const QString &unitName)
{
    auto manager = managerInterface();
    if(!isValidManager(manager, QStringLiteral("GetUnit")))
        return {};

    const QDBusReply<QDBusObjectPath> reply = manager.call(QStringLiteral("GetUnit"), unitName);
    if(!reply.isValid())
    {
        logReplyError(QStringLiteral("GetUnit(%1)").arg(unitName), reply.error());
        return {};
    }

    return reply.value();
}

QString unitProperty(const QString &unitName, const QString &propertyName)
{
    const QDBusObjectPath path = unitObjectPath(unitName);
    if(path.path().isEmpty())
        return {};

    QDBusInterface properties(SYSTEMD_BUS_NAME,
                              path.path(),
                              DBUS_PROPERTIES_INTERFACE,
                              QDBusConnection::systemBus());
    if(!properties.isValid())
    {
        qWarning() << "Cannot access systemd unit properties for" << unitName << ":" << properties.lastError().message();
        return {};
    }

    const QDBusReply<QDBusVariant> reply = properties.call(QStringLiteral("Get"),
                                                            QString::fromLatin1(SYSTEMD_UNIT_INTERFACE),
                                                            propertyName);
    if(!reply.isValid())
    {
        logReplyError(QStringLiteral("Get(%1.%2)").arg(unitName, propertyName), reply.error());
        return {};
    }

    return reply.value().variant().toString();
}

bool callUnitMethod(const QString &methodName, const QString &unitName)
{
    auto manager = managerInterface();
    if(!isValidManager(manager, methodName))
        return false;

    const QDBusMessage reply = manager.call(methodName, unitName, QString::fromLatin1(REPLACE_JOB_MODE));
    return isSuccessful(reply, QStringLiteral("%1(%2)").arg(methodName, unitName));
}

bool callUnitFilesMethod(const QString &methodName, const QStringList &unitNames, bool runtime, bool force)
{
    auto manager = managerInterface();
    if(!isValidManager(manager, methodName))
        return false;

    const QDBusMessage reply = manager.call(methodName,
                                             QVariant::fromValue(unitNames),
                                             QVariant(runtime),
                                             QVariant(force));
    return isSuccessful(reply, QStringLiteral("%1(%2)").arg(methodName, unitNames.join(QLatin1Char(','))));
}
} // namespace

QString SystemdManager::getUnitFileState(const QString &unitName)
{
    auto manager = managerInterface();
    if(!isValidManager(manager, QStringLiteral("GetUnitFileState")))
        return {};

    const QDBusReply<QString> reply = manager.call(QStringLiteral("GetUnitFileState"), unitName);
    if(!reply.isValid())
    {
        logReplyError(QStringLiteral("GetUnitFileState(%1)").arg(unitName), reply.error());
        return {};
    }

    return reply.value();
}

QString SystemdManager::activeState(const QString &unitName)
{
    return unitProperty(unitName, QStringLiteral("ActiveState"));
}

bool SystemdManager::isUnitActive(const QString &unitName)
{
    return activeState(unitName) == QLatin1String("active");
}

bool SystemdManager::isUnitEnabled(const QString &unitName)
{
    return getUnitFileState(unitName) == QLatin1String("enabled");
}

bool SystemdManager::unitFileExists(const QString &unitName)
{
    return !getUnitFileState(unitName).isEmpty();
}

bool SystemdManager::startUnit(const QString &unitName)
{
    return callUnitMethod(QStringLiteral("StartUnit"), unitName);
}

bool SystemdManager::stopUnit(const QString &unitName)
{
    return callUnitMethod(QStringLiteral("StopUnit"), unitName);
}

bool SystemdManager::restartUnit(const QString &unitName)
{
    return callUnitMethod(QStringLiteral("RestartUnit"), unitName);
}

bool SystemdManager::reload()
{
    auto manager = managerInterface();
    if(!isValidManager(manager, QStringLiteral("Reload")))
        return false;

    return isSuccessful(manager.call(QStringLiteral("Reload")), QStringLiteral("Reload"));
}

bool SystemdManager::enableUnitFiles(const QStringList &unitNames, bool runtime, bool force)
{
    return callUnitFilesMethod(QStringLiteral("EnableUnitFiles"), unitNames, runtime, force);
}

bool SystemdManager::disableUnitFiles(const QStringList &unitNames, bool runtime)
{
    return callUnitFilesMethod(QStringLiteral("DisableUnitFiles"), unitNames, runtime, false);
}
