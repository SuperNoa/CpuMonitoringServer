#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtNetwork>
#include <memory>

class Connection;

class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = nullptr);

signals:
    void newConnection(Connection *connection);

public slots:

private:
    void initServer();

    QTcpServer *tcpServer = nullptr;
};

#endif // TCPSERVER_H
