#include <QQmlApplicationEngine>

#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlContext>

#include "TemperatureModel.h"
#include "TcpServer.h"

//  You are requested to create a small client-server application for monitoring the CPU
//  temperature of the client PC over a network.
//  The client reads the CPU temperature of the PC and sends it via network to the monitoring server every n seconds.
//  The rate of the temperature reading must be configurable by the user at launch time.
//  The server, once the client is connected, graphs the CPU temperature of the client PC on a plot.
//  If the temperature rises above a certain threshold that can be set by the user, then an alarm is raised.
//  You are required to use the Qt framework and C++ to develop the server.
//  You are free to choose how to develop the client (for example a Python solution might be easier to implement than a C++ based one)

int main(int argc, char *argv[])
{
    // Qt Charts uses Qt Graphics View Framework for drawing, therefore QApplication must be used.
    QApplication app(argc, argv);

    QQuickView viewer;
    // The following are needed to make examples run without having to install the module
    // in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    viewer.engine()->addImportPath(
                        extraImportPath.arg(QGuiApplication::applicationDirPath(),
                        QString::fromLatin1("qml"))
                    );

    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    TemperatureModel temperatureModel;
    TcpServer tcpServer { &temperatureModel };

    viewer.engine()->rootContext()->setContextProperty("_temperatureModel", &temperatureModel);

    viewer.setTitle(QStringLiteral("CPU Monitoring Server"));
    viewer.setSource(QUrl("qrc:/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

    return app.exec();
}
