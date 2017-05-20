#include "udpsocket.h"
#include "game.h"
#include <QDebug>
#include <QNetworkDatagram>

extern Game *game;

UdpSocket::UdpSocket(QObject *parent) : QObject(parent)
{
    socket = new QUdpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()));
    socket->bind(700);
}

void UdpSocket::write(QString code)
{
    QByteArray data;
    data.append(code);
    socket->writeDatagram(data,opponentIP,700);
    qDebug() << "write: " << code << ", to: " << opponentIP;
}

void UdpSocket::writeACK()
{
    write(ack);
}

void UdpSocket::processData(QNetworkDatagram datagram)
{
    if (datagram.data() == spwn)
        game->spawnEnemy();
    if (datagram.data() == ack)
    {
        game->opponentConnected = true;
        opponentIP = datagram.senderAddress();
    }
}

QHostAddress UdpSocket::getOpponentIP() const
{
    return opponentIP;
}

void UdpSocket::setOpponentIP(const QHostAddress &value)
{
    opponentIP = value;
}

void UdpSocket::read()
{
    while (socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        processData(datagram);
        qDebug() << "Recieved: " << datagram.data();
    }
}
