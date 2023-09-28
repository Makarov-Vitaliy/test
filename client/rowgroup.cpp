#include "rowgroup.h"

RowGroup::RowGroup(const Params &params) : parametres(params)
{
	text_label = new QLabel(params.text);
	text_value = new QLabel("");//QString::number(parametres.curr_value));
    text_value->setFixedHeight(20);

	if (parametres.text_width>0) {
		text_label->setFixedWidth(parametres.text_width);
	}

	if (parametres.curr_width>0) {
		text_value->setFixedWidth(parametres.curr_width);
	}

	text_label->setAlignment(parametres.align);

	hlayout = new QHBoxLayout();

	hlayout->addWidget(text_label);
	hlayout->addWidget(text_value);
    hlayout->setMargin(0);
	setLayout(hlayout);
}

void RowGroup::update_value(qreal data)
{
	text_value->setText(QString::number(data,'g',3));
}

//void RowGroup::update_data(const QString & data)
//{
//	text_label->setText(data);
//}


