#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork>
#include <memory>

class Connection;

class TcpServer : public QTcpServer
{

public:
    TcpServer(QObject *parent = nullptr);

signals:
    void newConnection(Connection *connection);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    void initServer();

    QTcpServer *tcpServer = nullptr;
};

#endif // TCPSERVER_H
