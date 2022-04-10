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

    if ( !m_tcpServer->listen(m_hostAddress, m_port) )
    {
        qWarning() << tr("Unable to start the server: %1.").arg( m_tcpServer->errorString() );

        m_tcpServer->close();
        return;
    }

    qDebug() << tr("The server starts listen for incoming connections at %1 on port %2.").arg( m_hostAddress.toString() ).arg( QString::number(m_port) );
}
