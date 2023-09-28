#include "column_combo.h"
#include "qobjectdefs.h"
#include <QDebug>

Column_combo::Column_combo(const Params &params): parametres(params)
{
	header_label = new QLabel(parametres.text);
    header_label->setFixedHeight(20);
	header_label->setAlignment(Qt::AlignHCenter);

	combo = new QComboBox();
    combo->setFixedHeight(20);
	combo->setMinimumWidth(parametres.text_width);
	//combo->setAlignment(Qt::AlignHCenter);
	vlayout=new QVBoxLayout();
	vlayout->addWidget(header_label);
	vlayout->addWidget(combo);
    vlayout->setMargin(0);
    setLayout(vlayout);

	connect(combo,SIGNAL(activated(const QString &)),this, SIGNAL(data_changed(const QString &)));
}

void Column_combo::set_data_combo(const QStringList &list, int active)
{
    combo->addItems(list);
    if (active<list.count()) {
        combo->setCurrentIndex(active);
    }
}
