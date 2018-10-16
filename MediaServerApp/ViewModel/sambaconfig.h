#ifndef SAMBACONFIG_H
#define SAMBACONFIG_H

#include <QObject>

class SambaConfig : public QObject
{
    Q_OBJECT
public:
    explicit SambaConfig(QObject *parent = nullptr);
    Q_INVOKABLE void bSave_onClicked(QString text);

public slots:


};

#endif // SAMBACONFIG_H
