#include "mainwindow.h"
#include <QProcess>
#include <QNetworkAccessManager>
#include <QNetworkReply>

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{

}

void MainWindow::savePassword(const QString password)
{
    QProcess process;
    QString commend = "echo -e " + password + "\n" + password + " | passwd root";
    QStringList commend_new;
    commend_new << "-c" << commend;
    process.start("bash", commend_new);
    while(process.waitForFinished());
    process.close();
}

void MainWindow::checkNetwork(QObject *bExit, QObject *timer)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.google.com"));
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QIODevice::readyRead, [this,reply,timer,bExit]()
    {
        // Network works
        timer->setProperty("running", QVariant(false));
        bExit->setProperty("enabled",QVariant(true));
    });
}

void MainWindow::updateConfig()
{
    QProcess::startDetached("bash /opt/installScriptYocto.sh");
}
