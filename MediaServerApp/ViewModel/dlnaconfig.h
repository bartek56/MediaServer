#ifndef DLNACONFIG_H
#define DLNACONFIG_H
#include <QtQuick>

class DlnaConfig : public QObject
{
    Q_OBJECT

public:
    explicit DlnaConfig(QObject *parent = nullptr);
};

#endif // DLNACONFIG_H
