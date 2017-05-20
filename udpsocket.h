#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>

using namespace std;

class UdpSocket : public QObject
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = 0);
    void write(QString code);
    void writeACK();

    //UDP codewords
    const QString spwn = "spwn"; //send new enemy to opponent
    const QString ack = "ACK";

    QHostAddress getOpponentIP() const;
    void setOpponentIP(const QHostAddress &value);

private:
    QUdpSocket *socket;
    void processData(QNetworkDatagram datagram);

    QHostAddress opponentIP;

signals:

private slots:
    void read();

public slots:
};

#endif // UDPSOCKET_H
