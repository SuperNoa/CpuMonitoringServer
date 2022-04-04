#include "TcpServer.h"

#include <qDebug>

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    //listen(QHostAddress::Any);

    initServer();

//    connect(tcpServer, &QTcpServer::newConnection, this, &Server::sendFortune);

    connect(tcpServer, &QTcpServer::newConnection, [this]
        {
//            QByteArray block;
//            QDataStream out(&block, QIODevice::WriteOnly);
//            out.setVersion(QDataStream::Qt_5_10);
//            out << fortunes[QRandomGenerator::global()->bounded(fortunes.size())];

            QTcpSocket *clientConnection = tcpServer->nextPendingConnection();

            connect(clientConnection, &QAbstractSocket::disconnected,
                    clientConnection, &QObject::deleteLater);

            clientConnection->readAll();
            clientConnection->disconnectFromHost();
        }
    );

    connect(tcpServer, &QIODevice::readyRead, [this]
        {

        }
    );

    connect(tcpServer, &QAbstractSocket::errorOccurred, [this]
        {

        }
     );
}

void TcpServer::initServer()
{
    tcpServer = new QTcpServer(this);

    if ( !tcpServer->listen() )
    {
        qDebug() << tr("Unable to start the server: %1.").arg( tcpServer->errorString() );

        close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if ( ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address() )
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if ( ipAddress.isEmpty() )
    {
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

        qDebug() << tr("The server is running on\n\nIP: %1\nport: %2\n\n").arg(ipAddress).arg( tcpServer->serverPort() );
    }
}

//void TcpServer::incomingConnection(qintptr socketDescriptor)
//{
//    Connection *connection = new Connection(socketDescriptor, this);

//    emit newConnection(connection);
//}
