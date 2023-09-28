#ifndef CAMERAFIELD_H
#define CAMERAFIELD_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <QtSvg/QSvgWidget>
#include <QIcon>
#include <QSvgRenderer>
#include <QJsonObject>
//#include "mainwindow.h"

class CameraField : public QWidget
{
	Q_OBJECT
public:
	struct DataSend{
		operator bool() const {
			return angle>0;
		}
		qreal angle=-1;
		qreal hoffset=0;
		qreal voffset=0;
	};

	explicit CameraField();

private slots:
    void paintEvent(QPaintEvent *) override;

public slots:
	void update_data(QJsonObject data);
	void update_cross_color (const QString & color);
	void update_back_color (const QString & color);

private:
	QRectF calculate(const CameraField::DataSend &data, int width, int height);
	int heightForWidth(int width) const override;
	QScopedPointer<QSvgRenderer> cross;
	DataSend m_data;
	QRectF m_rect;
	Qt::GlobalColor color_back=Qt::black;

signals:

};

#endif // CAMERAFIELD_H
