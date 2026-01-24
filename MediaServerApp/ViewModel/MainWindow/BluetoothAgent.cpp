#include "BluetoothAgent.h"


BluetoothAgent::BluetoothAgent(QObject *parent)
    : QObject(parent)
{
}


void BluetoothAgent::RequestConfirmation(const QDBusObjectPath &device, uint passkey) {
    qInfo() << "RequestConfirmation for" << device.path() << "passkey" << passkey;

    pendingConfirmation = message();
    pendingDevicePath = device.path();
    QString deviceName = pendingDevicePath.section('/',-1);

    QDBusInterface props(
            "org.bluez",
            pendingDevicePath,
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
            );

    if (props.isValid())
    {
        QDBusReply<QVariant> reply = props.call(
                "Get",
                "org.bluez.Device1",
                "Alias"
                );
        if (reply.isValid())
        {
            deviceName = reply.value().toString();
        }
    }

    setDelayedReply(true);

    emit confirmPairingRequested(deviceName, passkey);
}


Q_INVOKABLE void BluetoothAgent::respondConfirmation(bool accepted) {
    //if (!pendingConfirmation.isValid())
    //    return;

    if (accepted) {
        setTrusted(QDBusObjectPath(pendingDevicePath));
        QDBusConnection::systemBus().send(pendingConfirmation.createReply());
        qInfo() << "Pairing confirmed by UI";
    } else {
        QDBusMessage err = pendingConfirmation.createErrorReply(
                "org.bluez.Error.Rejected",
                "User rejected pairing"
                );
        QDBusConnection::systemBus().send(err);
        qInfo() << "Pairing rejected by UI";
    }

    pendingConfirmation = QDBusMessage();
    pendingDevicePath.clear();
}


Q_INVOKABLE void BluetoothAgent::respondAuthorization(bool accepted) {
    //if (!pendingAuthorization.isValid())
    //    return;

    if (accepted) {
        setTrusted(QDBusObjectPath(pendingDevicePath));
        QDBusConnection::systemBus().send(pendingAuthorization.createReply());
        qInfo() << "Authorization granted by UI";
    } else {
        QDBusMessage err = pendingAuthorization.createErrorReply(
                "org.bluez.Error.Rejected",
                "User rejected authorization"
                );
        QDBusConnection::systemBus().send(err);
        qInfo() << "Authorization rejected by UI";
    }

    pendingAuthorization = QDBusMessage();
    pendingDevicePath.clear();
}

void BluetoothAgent::setTrusted(const QDBusObjectPath &devicePath) {
    QDBusInterface props = QDBusInterface(
            "org.bluez",
            devicePath.path(),
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
            );

    if (!props.isValid()) {
        qWarning() << "Cannot access Properties interface for" << devicePath.path();
        return;
    }

    QDBusReply<void> reply = props.call(
            "Set",
            "org.bluez.Device1",
            "Trusted",
            QVariant::fromValue(QDBusVariant(true))
            );

    if (!reply.isValid()) {
        qWarning() << "Failed to set Trusted:" << reply.error().message();
    } else {
        qInfo() << "Device marked as Trusted";
    }
}

