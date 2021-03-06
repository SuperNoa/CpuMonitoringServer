#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork>
#include <memory>

#include "TemperatureModel.h"

class Connection;

class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(
            TemperatureModel* temperatureModel,
            QString serverAddress = "",
             int serverPort = 0,
            QObject *parent = nullptr);

signals:
    void newConnection(Connection *connection);

public slots:

private:
    void initServer();

    QTcpServer*     m_tcpServer { nullptr };

    QHostAddress    m_hostAddress;
    quint16         m_port { 0 };

    TemperatureModel* m_temperatureModel;
};

#endif // TCPSERVER_H
