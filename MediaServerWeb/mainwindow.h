#ifndef MAIN_H
#define MAIN_H

#include <QObject>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MAIN_H
