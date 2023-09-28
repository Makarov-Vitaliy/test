#ifndef UDPRECIEVER_H
#define UDPRECIEVER_H

#include <QObject>
#include <QJsonObject>
#include <QtNetwork/QUdpSocket>
#include "camera_field.h"
#include "constants.h"

class UdpReciever : public QObject
{
    Q_OBJECT
public:
    explicit UdpReciever();
    ~UdpReciever();

signals:
    void finished();
	void data_recieved(const QByteArray &data);
    void error(QString err);
	void dataReady(QJsonObject data);

private slots:
	void start();
	void readyRead();
private:
    QUdpSocket *udp_socket;


};

#endif // UDPRECIEVER_H
