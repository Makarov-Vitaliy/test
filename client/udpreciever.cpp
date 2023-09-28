#include "udpreciever.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include <QMessageBox>


UdpReciever::UdpReciever()
{

}

UdpReciever::~UdpReciever()
{

}

void UdpReciever::start() {
	udp_socket = new QUdpSocket(this);
	if (udp_socket->bind(QHostAddress::LocalHost, Constants::port_recieve)!=true) {
		//QMessageBox::critical(this, tr("Error"), tr("Could not bind to port"));
		qDebug()<<"error binding";
		return;
	}

	connect(udp_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void UdpReciever::readyRead()
{
    QByteArray buffer;
    buffer.resize(udp_socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    udp_socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);

    if (senderPort==50000) {

        QJsonDocument jdoc = QJsonDocument::fromJson(buffer);

        if (jdoc.isObject() && !jdoc.isNull()) {
            QJsonObject response = jdoc.object();

			if (!response["angle"].isUndefined()
					&& (!response["hoffset"].isUndefined())
					&& (!response["voffset"].isUndefined())) {

				emit dataReady(response);
				qDebug()<<"===="<<response["angle"]<<"=="<<response["hoffset"];
			}
        }
    }
}

