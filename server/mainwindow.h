#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QFutureWatcher>
#include <QtNetwork/QUdpSocket>
#include "rowgroup.h"


class MainWindow : public QWidget
{
	Q_OBJECT

	struct DataSend{
		qreal angle=3.0;
		qreal hoffset = 0.0;
		qreal voffset = 0.0;
	};

public:
	MainWindow();
	~MainWindow();

private slots:
	void onSendClicked();
protected:
	void closeEvent(QCloseEvent *event) override;
private:
	void sendUdp(const DataSend & datav);
	void fill_data();
	void writeSettings();
	void readSettings();
	RowGroup *angle_group;
	RowGroup *hoffset_group;
	RowGroup *voffset_group;
	QVBoxLayout *vlayout;
	QPushButton *btn_send;
	QFutureWatcher<void> watcher;
	DataSend data_send;
};
#endif // MAINWINDOW_H
