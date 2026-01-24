#ifndef BLUETOOTHAGENT_H
#define BLUETOOTHAGENT_H

#include <QDBusContext>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusObjectPath>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusVariant>
#include <QObject>
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

public slots:
    void Release() {
        qInfo() << "Agent released";
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

    void RequestConfirmation(const QDBusObjectPath &device, uint passkey);

    void RequestAuthorization(const QDBusObjectPath &device) {
        qInfo() << "RequestAuthorization for" << device.path();
    }

    void Cancel() {
        qInfo() << "Pairing canceled";
        pendingConfirmation = QDBusMessage();
        pendingAuthorization = QDBusMessage();
        pendingDevicePath.clear();
    }

    Q_INVOKABLE void respondConfirmation(bool accepted);

    Q_INVOKABLE void respondAuthorization(bool accepted);

private:
    QObject *messageDialog = nullptr;

    QDBusMessage pendingConfirmation;
    QDBusMessage pendingAuthorization;
    QString pendingDevicePath;

    void setTrusted(const QDBusObjectPath &devicePath);
};

#endif// BLUETOOTHAGENT_H
