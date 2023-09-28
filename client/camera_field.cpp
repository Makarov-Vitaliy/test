#include "camera_field.h"
#include <QPainter>
#include <QDebug>


CameraField::CameraField()
{
    QSizePolicy policy(sizePolicy());
    policy.setHeightForWidth(true);
	setSizePolicy(policy);
	cross.reset(new QSvgRenderer(QString(":/crosshair red.svg")));
}

void CameraField::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.fillRect(this->rect(),color_back);
	painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(this->width()>>1, (this->height()>>1) -30, this->width()>>1, (this->height()>>1) +30);
    painter.drawLine((this->width()>>1)-30, (this->height()>>1), (this->width()>>1)+30, (this->height()>>1));

	//cross->setAspectRatioMode(Qt::KeepAspectRatio);
	if (m_data) {
		m_rect=calculate(m_data, this->width(), this->height());
		cross->render(&painter,m_rect);
	}
}

void CameraField::update_data(QJsonObject data)
{
	m_data.angle=data["angle"].toDouble();
	m_data.hoffset=data["hoffset"].toDouble();
	m_data.voffset=data["voffset"].toDouble();

	this->update();
	qDebug()<<data;
}

void CameraField::update_cross_color(const QString &color)
{
	if (color=="Черный") {
		cross.reset(new QSvgRenderer(QString(":/crosshair black.svg")));
	} else {
		cross.reset(new QSvgRenderer(QString(":/crosshair red.svg")));
	}

	this->update();
}

void CameraField::update_back_color(const QString &color)
{
	if (color=="Черный") {
		color_back=Qt::black;
	} else if (color=="Серый"){
		color_back=Qt::gray;
	} else if (color=="Белый"){
		color_back=Qt::white;
	}

	this->update();
}

QRectF CameraField::calculate(const CameraField::DataSend &data, int width, int height)
{
	QRectF res;
	int halfwidth = (width>>1);
	int halfheght = (height>>1);
	qreal x1=halfwidth + data.hoffset*(halfwidth);
	qreal y1=halfheght + data.voffset*(halfheght);
	qreal w=data.angle*6000.0*50.0/360.0;
	qreal dec = width/w;

	res.setCoords(x1-(dec*512),y1-(dec*512),x1+dec*512.0,y1+dec*512.0);
	return res;
}

int CameraField::heightForWidth(int width) const
{
    return width*3.0/4.0;
}
