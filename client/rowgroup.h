#ifndef ROWGROUP_H
#define ROWGROUP_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>
#include <camera_field.h>

class RowGroup : public QWidget
{
	Q_OBJECT
public:

	struct Params{
		QString text;
		qreal curr_value;
		Qt::Alignment align=Qt::AlignHCenter;
		int text_width=0;
		int curr_width=0;
	};

	explicit RowGroup(const Params &params);

public slots:
	void update_value(qreal dat);

private:
	qreal m_value;
	QLabel *text_label;
	QLabel *text_value;
	QHBoxLayout *hlayout;
	Params parametres;

signals:

};

#endif // ROWGROUP_H
