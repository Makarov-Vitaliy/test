#include "rowgroup.h"
#include "constants.h"
#include <QDebug>

RowGroup::RowGroup(const Params &params) : parametres(params)
{
	text_label = new QLabel(params.text);
	text_value = new QLabel(QString::number(parametres.curr_value));

	if (parametres.text_width>0) {
		text_label->setFixedWidth(parametres.text_width);
	}

	if (parametres.curr_width>0) {
		text_value->setFixedWidth(parametres.curr_width);
	}

	text_label->setAlignment(parametres.align);
	//text_value->setN
	slider = new QSlider(Qt::Horizontal);
	slider->setMinimumWidth(70);
	slider->setMinimum(0);
	slider->setMaximum(Constants::slider_int);
	slider->setTickPosition(QSlider::TicksBothSides);
	slider->setTickInterval(parametres.tickInterval);
	slider->setValue(get_slider_value(parametres.curr_value));
	hlayout = new QHBoxLayout();

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

	hlayout->addWidget(text_label);
	hlayout->addWidget(slider);
	hlayout->addWidget(text_value);
	setLayout(hlayout);
}

qreal RowGroup::get_current_value()
{
	return text_value->text().toDouble();
}

void RowGroup::setValue(const int &value)
{
	//Q_ASSERT(parametres.max_value==parametres.min_value);

	if (slider->maximum()!=slider->minimum()) {
		qreal step = (parametres.max_value-parametres.min_value)/static_cast<qreal>(slider->maximum()-slider->minimum());
		text_value->setNum((parametres.min_value+ value*step));
	}
}

int RowGroup::get_slider_value(const qreal &val)
{
	if (parametres.min_value> val) {
		return 0;
	}

	qreal step = (parametres.max_value-parametres.min_value)/static_cast<qreal>(slider->maximum()-slider->minimum());

	return (val-parametres.min_value)/step;

}
