#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include <mainwindow.h>

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    MainWindow mainWindow;
    engine.rootContext()->setContextProperty("MainWindow",&mainWindow);

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

