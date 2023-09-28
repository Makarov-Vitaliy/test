#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QJsonObject>
#include <QtNetwork/QUdpSocket>
#include <QSpacerItem>
#include "camera_field.h"
#include "rowgroup.h"
#include "column_combo.h"


class MainWindow : public QWidget
{
	Q_OBJECT

public:

	MainWindow();
	~MainWindow();

public slots:
	void update_data(QJsonObject data);

private:
	CameraField *camera;
	RowGroup *angle;
	RowGroup *hoffset;
	RowGroup *voffset;
	Column_combo *column_background;
    Column_combo *column_cross;
    QSpacerItem *vertSpacer;
	QVBoxLayout *vlayout;
    QVBoxLayout *vlayout_backcolor;
    QVBoxLayout *vlayout_crosscolor;
    QVBoxLayout *vlayout_data;
    QHBoxLayout *hlayout;
	QPushButton *btn_send;
};
#endif // MAINWINDOW_H
