#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>
#include <QStringList>
#include <QMap>

class Constants
{
public:
    Constants();
    static const QStringList light_theme;
    static const QStringList dark_theme;
    static const QMap<QString,QStringList> colors_map;

	static constexpr uint16_t port_transmit=50000;
	static constexpr uint16_t port_recieve=55000;

    static QMap<QString, QStringList> getColors_map();
};

#endif // CONSTANTS_H
