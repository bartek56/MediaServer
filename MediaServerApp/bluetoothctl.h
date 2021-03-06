#ifndef BLUETOOTHCTL_H
#define BLUETOOTHCTL_H

#include <QObject>
#include <QProcess>

class Bluetoothctl : public QObject
{
    Q_OBJECT
public:
    explicit Bluetoothctl(QObject *parent = nullptr);
    void pair();
    void trust();
    void cancel();
    void setMessageDialog(QObject *messageDialog);
    ~Bluetoothctl();

signals:

public slots:
    void readOutput();

private:
    QProcess *process;
    QObject *messageDialog;
    QString deviceName;
    QString macNumber;

};

#endif // BLUETOOTHCTL_H
