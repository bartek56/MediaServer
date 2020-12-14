#ifndef MAIN_H
#define MAIN_H

#include <QObject>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);
    Q_INVOKABLE void savePassword(const QString password);
    Q_INVOKABLE void checkNetwork(QObject *bExit, QObject *timer);
    Q_INVOKABLE void updateConfig();

};

#endif // MAIN_H
