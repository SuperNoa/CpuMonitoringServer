#include "TcpServer.h"

#include <QDebug>

TcpServer::TcpServer(
        TemperatureModel* temperatureModel,
        QString serverAddress,
        int serverPort,
        QObject *parent) :
    m_temperatureModel { temperatureModel },
    m_hostAddress { serverAddress },
    m_port { static_cast<quint16>(serverPort) },
    QObject(parent)
{
    initServer();

    connect(m_tcpServer, &QTcpServer::newConnection, [this]
        {
            QTcpSocket* clientSocket { m_tcpServer->nextPendingConnection() };

            qInfo() << "New connection received!";

            // readyRead signal is emitted when data has been received
            connect(clientSocket, &QIODevice::readyRead, [this, clientSocket]
                {
                    QDataStream in;
                    in.setDevice(clientSocket);
                    // Set the protocol version of QDataStream to Version 20 (Qt 6.0)
                    in.setVersion(QDataStream::Qt_6_2);

                    in.startTransaction();

                    int receivedMessage {0};
                    in >> receivedMessage;

//                    qDebug() << "New message received!";
//                    qDebug() << receivedMessage;

                    m_temperatureModel->setCpuTemperature(receivedMessage);

                    if ( !in.commitTransaction() )
                        return;

                    //clientSocket->disconnectFromHost();
                }
            );

            connect(clientSocket, &QAbstractSocket::errorOccurred, [this, &clientSocket] (QAbstractSocket::SocketError socketError)
                {
                     //qDebug() << tr("The following error occurred: %1.").arg( clientSocket->errorString() );
                }
            );

            connect(clientSocket, &QAbstractSocket::disconnected, clientSocket, &QObject::deleteLater);
        }
    );

}

void TcpServer::initServer()
{
    m_tcpServer = new QTcpServer(this);

//    m_hostAddress = QHostAddress::LocalHost;
//    m_port = 5000;

    if ( !m_tcpServer->listen(m_hostAddress, m_port) )
    {
        qWarning() << tr("Unable to start the server: %1.").arg( m_tcpServer->errorString() );

        m_tcpServer->close();
        return;
    }

    qDebug() << tr("The server starts listen for incoming connections at %1 on port %2.").arg( m_hostAddress.toString() ).arg( QString::number(m_port) );


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
