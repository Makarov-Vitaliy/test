#ifndef COLUMN_COMBO_H
#define COLUMN_COMBO_H

#include <QWidget>
#include <QObject>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>

class Column_combo: public QWidget
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

	explicit Column_combo(const Params &params);
    void set_data_combo(const QStringList &list, int active);


private:
	QLabel *header_label;
	QComboBox *combo;
	QVBoxLayout *vlayout;
	Params parametres;

signals:
    void data_changed(const QString &str);
};

#endif // COLUMN_COMBO_H
