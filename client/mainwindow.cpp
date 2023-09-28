#include "mainwindow.h"
#include "udpreciever.h"
#include "constants.h"
#include <QtConcurrent/QtConcurrent>
#include <QtNetwork/QUdpSocket>

MainWindow::MainWindow()
{

	vlayout = new QVBoxLayout();
	camera = new CameraField();
	camera->setMinimumSize(QSize(400,300));

    vlayout->addWidget(camera);
	vlayout->addStretch(1);
    QWidget *containerWidget = new QWidget();

    hlayout = new QHBoxLayout(containerWidget);
	containerWidget->setFixedHeight(100);

    //vlayout->addItem(vertSpacer);
    vlayout->addWidget(containerWidget);

    vlayout_backcolor = new QVBoxLayout();
    vlayout_backcolor->setAlignment(Qt::AlignBottom);
    hlayout->addLayout(vlayout_backcolor);

    vlayout_crosscolor = new QVBoxLayout();
    hlayout->addLayout(vlayout_crosscolor);
    vlayout_crosscolor->setAlignment(Qt::AlignBottom);

    vlayout_data= new QVBoxLayout();
    vlayout_data->setAlignment(Qt::AlignBottom);
    hlayout->addLayout(vlayout_data);

	RowGroup::Params params;
	params.text="Угол камеры по горизонтали, град";
	params.text_width=250;
	params.curr_width=50;
	params.align=Qt::AlignHCenter | Qt::AlignVCenter;

	angle= new RowGroup(params);

	params.text="Отступ по горизонтали";
	hoffset= new RowGroup(params);

	params.text="Отступ по вертикали";
	voffset = new RowGroup(params);

	Column_combo::Params column_params;
    column_params.text="Цвет фона";
	column_params.text_width=180;
    //column_params.list<<Constants::colors_map.keys();
	column_background = new Column_combo(column_params);
	column_background->set_data_combo(Constants::colors_map.keys(), 2);
    column_params.text="Цвет прицела";
    column_cross = new Column_combo(column_params);
    column_cross->set_data_combo(Constants::colors_map.value((Constants::colors_map.firstKey())), 0);

	setLayout(vlayout);
    vlayout_data->addWidget(angle);
    vlayout_data->addWidget(hoffset);
    vlayout_data->addWidget(voffset);
    vlayout_backcolor->addWidget(column_background);
	vlayout_crosscolor->addWidget(column_cross);
	setWindowTitle("Клиент");

    QThread* thread = new QThread;
    UdpReciever* udp_worker = new UdpReciever();
    udp_worker->moveToThread(thread);

	connect(thread, SIGNAL(started()), udp_worker, SLOT(start()));
    connect(udp_worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(udp_worker, SIGNAL(finished()), udp_worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	connect(udp_worker, SIGNAL(dataReady(QJsonObject )), camera, SLOT(update_data(QJsonObject )));
	connect(udp_worker, SIGNAL(dataReady(QJsonObject )), this, SLOT(update_data(QJsonObject )));
	connect(column_cross, SIGNAL(data_changed(const QString &)), camera,SLOT(update_cross_color(const QString & )));
	connect(column_background, SIGNAL(data_changed(const QString &)), camera,SLOT(update_back_color(const QString & )));
    thread->start();

}

MainWindow::~MainWindow()
{
}

void MainWindow::update_data(QJsonObject data)
{
//	CameraField::DataSend dat;
//	dat.angle=data["angle"].toDouble();
//	dat.hoffset=data["hoffset"].toDouble();
//	dat.voffset=data["voffset"].toDouble();

	angle->update_value(data["angle"].toDouble());
	hoffset->update_value(data["hoffset"].toDouble());
	voffset->update_value(data["voffset"].toDouble());
}



