#ifndef BLUETOOTHAGENT_H
#define BLUETOOTHAGENT_H

#include <QObject>
#include <QDBusContext>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusObjectPath>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusVariant>
#include <QVariant>
#include <QDebug>

static const char *AGENT_PATH = "/bt/agent";

class BluetoothAgent : public QObject, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.bluez.Agent1")

public:
    explicit BluetoothAgent(QObject *parent = nullptr);

    // QML dialog (optional, jeśli chcesz trzymać wskaźnik jak u Ciebie)
    Q_INVOKABLE void setMessageDialog(QObject *dialogObject) {
        messageDialog = dialogObject;
    }

signals:
    void confirmPairingRequested(QString devicePath, uint passkey);
    void authorizationRequested(QString devicePath);

public slots:
    void Release() {
        qInfo() << "Agent released";
        //QCoreApplication::quit();
    }

    QString RequestPinCode(const QDBusObjectPath &device) {
        qInfo() << "PIN requested for" << device.path();
        return "0000";
    }

    uint RequestPasskey(const QDBusObjectPath &device) {
        qInfo() << "Passkey requested for" << device.path();
        return 123456;
    }

    void DisplayPinCode(const QDBusObjectPath &device, const QString &pincode) {
        qInfo() << "Display PIN" << pincode << "for" << device.path();
    }

    void DisplayPasskey(const QDBusObjectPath &device, uint passkey, ushort entered) {
        Q_UNUSED(entered)
        qInfo() << "Display passkey" << passkey << "for" << device.path();
    }

    // KLUCZ: delayed reply, bo czekamy na decyzję z UI
    void RequestConfirmation(const QDBusObjectPath &device, uint passkey) {
        qInfo() << "RequestConfirmation for" << device.path() << "passkey" << passkey;


        pendingConfirmation = message();            // zapisujemy oryginalną wiadomość DBus
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
                    "Alias"   // albo "Name"
                    );
            if (reply.isValid())
            {
                deviceName = reply.value().toString();
            }
        }

        setDelayedReply(true);

        emit confirmPairingRequested(deviceName, passkey);
    }

    void RequestAuthorization(const QDBusObjectPath &device) {
        qInfo() << "RequestAuthorization for" << device.path();

        setDelayedReply(true);
        pendingAuthorization = message();
        pendingDevicePath = device.path();

        emit authorizationRequested(device.path());
    }

    void Cancel() {
        qInfo() << "Pairing canceled";
        pendingConfirmation = QDBusMessage();
        pendingAuthorization = QDBusMessage();
        pendingDevicePath.clear();
    }

    // wołane z QML po kliknięciu "OK/Cancel"
    Q_INVOKABLE void respondConfirmation(bool accepted) {
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

    Q_INVOKABLE void respondAuthorization(bool accepted) {
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

private:
    void setTrusted(const QDBusObjectPath &devicePath) {
        QDBusInterface props(
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

private:
    QObject *messageDialog = nullptr;

    QDBusMessage pendingConfirmation;
    QDBusMessage pendingAuthorization;
    QString pendingDevicePath;
};

#endif// BLUETOOTHAGENT_H
