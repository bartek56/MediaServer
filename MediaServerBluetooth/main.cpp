#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusError>
#include <QDBusReply>
#include <QDBusAbstractAdaptor>
#include <QDBusObjectPath>
#include <QDBusInterface>
#include <QTextStream>
#include <QDebug>

static const char *AGENT_PATH = "/bt/agent";

class Agent : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.bluez.Agent1")

public:
    Agent(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    void Release()
    {
        qInfo() << "Agent released";
        QCoreApplication::quit();
    }

    QString RequestPinCode(const QDBusObjectPath &device)
    {
        qInfo() << "PIN requested for" << device.path();
        return "0000";
    }

    void DisplayPinCode(const QDBusObjectPath &device, const QString &pincode)
    {
        qInfo() << "Display PIN" << pincode << "for" << device.path();
    }

    uint RequestPasskey(const QDBusObjectPath &device)
    {
        qInfo() << "Passkey requested for" << device.path();
        return 123456;
    }

    void DisplayPasskey(const QDBusObjectPath &device, uint passkey, ushort entered)
    {
        Q_UNUSED(entered)
        qInfo() << "Display passkey" << passkey << "for" << device.path();
    }

    void RequestConfirmation(const QDBusObjectPath &device, uint passkey)
    {
        QTextStream in(stdin);
        QTextStream out(stdout);

        out << "\nPair device " << device.path()
            << " with passkey " << passkey << " ? (y/n): " << flush;

        QString response = in.readLine().trimmed().toLower();

        if (response != "y") {
            //QDBusError::
            //throw QDBusError(QDBusError::Failed);
            //throw QDBusError(
            //        "org.bluez.Error.Rejected",
            //        "User rejected pairing"
            //        );
            qInfo() << "wrong response";
        }
        setTrusted(device);

        qInfo() << "Pairing confirmed";
    }

    void RequestAuthorization(const QDBusObjectPath &device)
    {
        QTextStream in(stdin);
        QTextStream out(stdout);

        out << "\nAuthorize device " << device.path()
            << " ? (y/n): " << flush;

        QString response = in.readLine().trimmed().toLower();

        if (response != "y") {
            qInfo() << "wrong response 2";
            //throw QDBusError("org.bluez.Error.Rejected", "User rejected authorization");
        }

        qInfo() << "Authorization granted";
    }

    void Cancel()
    {
        qInfo() << "Pairing canceled";
    }

    void setTrusted(const QDBusObjectPath &devicePath)
    {
        QDBusInterface props(
                "org.bluez",
                devicePath.path(),
                "org.freedesktop.DBus.Properties",
                QDBusConnection::systemBus()
                );

        if (!props.isValid()) {
            qWarning() << "Cannot access Properties interface for"
                       << devicePath.path();
            return;
        }

        QDBusReply<void> reply = props.call(
                "Set",
                "org.bluez.Device1",
                "Trusted",
                QVariant::fromValue(QDBusVariant(true))
                );

        if (!reply.isValid()) {
            qWarning() << "Failed to set Trusted:"
                       << reply.error().message();
        } else {
            qInfo() << "Device marked as Trusted";
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QDBusConnection bus = QDBusConnection::systemBus();
    if (!bus.isConnected()) {
        qCritical() << "Cannot connect to system bus";
        return 1;
    }

    Agent agent;
    bus.registerObject(AGENT_PATH, &agent, QDBusConnection::ExportAllSlots);

    QDBusMessage registerAgent = QDBusMessage::createMethodCall(
            "org.bluez",
            "/org/bluez",
            "org.bluez.AgentManager1",
            "RegisterAgent");

    registerAgent << QDBusObjectPath(AGENT_PATH) << "KeyboardDisplay";
    bus.call(registerAgent);

    QDBusMessage requestDefault = QDBusMessage::createMethodCall(
            "org.bluez",
            "/org/bluez",
            "org.bluez.AgentManager1",
            "RequestDefaultAgent");

    requestDefault << QDBusObjectPath(AGENT_PATH);
    bus.call(requestDefault);

    qInfo() << "BlueZ agent registered. Waiting for pairing...";

    return app.exec();
}

#include "main.moc"
