#include "TcpServer.h"

#include <QDebug>

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    //listen(QHostAddress::Any);

    initServer();

    connect(tcpServer, &QTcpServer::newConnection, [this]
        {
            QTcpSocket *tcpSocket { tcpServer->nextPendingConnection() };

            qInfo() << "New connection received!";

            connect(tcpSocket, &QIODevice::readyRead, [this, tcpSocket]
                {
                    QByteArray message { tcpSocket->readAll() };

                    qDebug() << message;

//                    // Deserialize the data
//                    QJsonDocument doc { QJsonDocument::fromBinaryData( message ) };

//                    qInfo() << doc.toJson();

                    tcpSocket->disconnectFromHost();
                }
            );

        }
    );
}

void TcpServer::initServer()
{
    tcpServer = new QTcpServer(this);

    if ( !tcpServer->listen(QHostAddress::LocalHost, 5000) )
    {
        qDebug() << tr("Unable to start the server: %1.").arg( tcpServer->errorString() );

        qWarning() << "Unable to start the server: " << tcpServer->errorString();
        return;
    }

//    QString ipAddress;
//    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

//    // use the first non-localhost IPv4 address
//    for (int i = 0; i < ipAddressesList.size(); ++i)
//    {
//        if ( ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address() )
//        {
//            ipAddress = ipAddressesList.at(i).toString();
//            break;
//        }
//    }

//    // if we did not find one, use IPv4 localhost
//    if ( ipAddress.isEmpty() )
//    {
//        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

//        qDebug() << tr("The server is running on\n\nIP: %1\nport: %2\n\n").arg(ipAddress).arg( tcpServer->serverPort() );
//    }
}
