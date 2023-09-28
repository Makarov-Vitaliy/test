#ifndef ROWGROUP_H
#define ROWGROUP_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QHBoxLayout>

class RowGroup : public QWidget
{
	Q_OBJECT
public:

	struct Params{
		QString text;
		qreal min_value;
		qreal max_value;
		qreal curr_value;
		Qt::Alignment align=Qt::AlignHCenter;
		int text_width=0;
		int curr_width=0;
		int tickInterval=10;
	};

	explicit RowGroup(const Params &params);
	qreal get_current_value();
private slots:
	void setValue(const int & value);

private:
	int get_slider_value(const qreal & val);
	qreal m_value;
	QLabel *text_label;
	QLabel *text_value;
	QSlider *slider;
	QHBoxLayout *hlayout;
	Params parametres;

signals:

};

#endif // ROWGROUP_H
