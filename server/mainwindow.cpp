#include "mainwindow.h"
#include <QtConcurrent/QtConcurrent>
#include <QtNetwork/QUdpSocket>
#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QNetworkDatagram>
#include "constants.h"

MainWindow::MainWindow()
{

	readSettings();
	vlayout = new QVBoxLayout();

	RowGroup::Params params;
	params.curr_value=data_send.angle;
	params.text=Constants::angle_text;
	params.min_value=2.0;
	params.max_value=5.0;
	params.tickInterval=Constants::slider_int/(params.max_value-params.min_value);
	params.text_width=270;
	params.curr_width=50;
	params.align=Qt::AlignHCenter | Qt::AlignVCenter;
	angle_group = new RowGroup(params);

	params.curr_value=data_send.hoffset;
	params.text=Constants::hoffset_text;
	params.min_value=-1.0;
	params.max_value=1.0;
	params.tickInterval=Constants::slider_int/(params.max_value-params.min_value);
	hoffset_group = new RowGroup(params);

	params.curr_value=data_send.voffset;
	params.text= Constants::voffset_text;
	params.min_value=-1.0;
	params.max_value=1.0;
	params.tickInterval=Constants::slider_int/(params.max_value-params.min_value);
	voffset_group = new RowGroup(params);

	btn_send=new QPushButton();
	btn_send->setText("Отправить");

	vlayout->addWidget(angle_group);
	vlayout->addWidget(hoffset_group);
	vlayout->addWidget(voffset_group);
	vlayout->addWidget(btn_send);

	connect(btn_send, SIGNAL (clicked()), this, SLOT (onSendClicked()));

	setLayout(vlayout);
	setWindowTitle("Сервер");
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	fill_data();
	writeSettings();
	event->accept();
}

void MainWindow::writeSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	settings.setValue("geometry", saveGeometry());
	settings.setValue("angle",data_send.angle);
	settings.setValue("hoffset",data_send.hoffset);
	settings.setValue("voffset",data_send.voffset);
}

void MainWindow::readSettings()
{
	QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
	const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();

	if (geometry.isEmpty()) {
		const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
		resize(500, 180);
		move((availableGeometry.width() - width()) / 2,
			 (availableGeometry.height() - height()) / 2);
	} else {
		restoreGeometry(geometry);
	}

	data_send.angle = settings.value("angle",Constants::angle_def).toFloat();
	data_send.hoffset = settings.value("hoffset",Constants::hoffset_def).toFloat();
	data_send.voffset = settings.value("voffset",Constants::voffset_def).toFloat();
}

void MainWindow::onSendClicked()
{
	qDebug()<<"parent thread=="<<QThread::currentThreadId();
	if (watcher.isRunning()) {
		return;
	}
	fill_data();

	QFuture<void> f1= QtConcurrent::run(this, &MainWindow::sendUdp, data_send);
	watcher.setFuture(f1);
}

void MainWindow::sendUdp(const DataSend & data)
{
	QUdpSocket udpSocketSend;
	qDebug()<<"child thread=="<<QThread::currentThreadId();

	 if (udpSocketSend.bind(50000, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)==false)
//	 if (udpSocketSend.bind(50000)==false)
	{
		qDebug()<<"jops";
//		//QMessageBox::critical(this, tr("Error"), tr("Could not bind to port"));
		return;
	}

	QJsonObject json;
	json["angle"]=data.angle;
	json["hoffset"]=data.hoffset;
	json["voffset"]=data.voffset;

	QJsonDocument json_doc(json);
	QByteArray buffer=json_doc.toJson();

	qint64 writeLen= udpSocketSend.writeDatagram(buffer, QHostAddress::LocalHost, 55000);
	if (writeLen!=buffer.count()) {
		qDebug()<<"Error written";
	}
	udpSocketSend.waitForBytesWritten(500);
	udpSocketSend.close();

}

void MainWindow::fill_data()
{
	data_send.angle=angle_group->get_current_value();
	data_send.hoffset=hoffset_group->get_current_value();
	data_send.voffset=voffset_group->get_current_value();
}



