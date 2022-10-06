#include "MainWindow.h"
#include <QProcess>
#include <QNetworkAccessManager>
#include <QNetworkReply>

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
}

void MainWindow::savePassword(const QString password)
{
    QProcess process;
    QString commend = "echo -e \"" + password + "\n" + password + "\" | passwd root";
    QStringList commend_new;
    commend_new << "-c" << commend;
    process.start("bash", commend_new);
    while(process.waitForFinished())
        ;
    process.close();

    QProcess process2;
    QString commend2 = "sed -i 's/\"rpc-password\".*/\"rpc-password\": \"" + password + "\",/g' /etc/transmission-daemon/settings.json";
    QStringList commend_new2;
    commend_new2 << "-c" << commend2;
    process2.start("bash", commend_new2);
    while(process2.waitForFinished())
        ;
    process2.close();
    //    sed -i 's/"rpc-password".*/"rpc-password": "transmission",/g'  /etc/transmission-daemon/settings.json
}

void MainWindow::checkNetwork(QObject *bExit, QObject *timer)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.google.com"));
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QIODevice::readyRead,
            [this, reply, timer, bExit]()
            {
                // Network works
                timer->setProperty("running", QVariant(false));
                bExit->setProperty("enabled", QVariant(true));
            });
}

void MainWindow::updateConfig()
{
    QProcess::startDetached("bash", QStringList() << "-c"
                                                  << "/opt/installScriptYocto.sh");
}
