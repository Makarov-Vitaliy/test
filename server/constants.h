#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QString>

class Constants
{
public:
	Constants();

	static const QString angle_text;
	static const QString hoffset_text;
	static const QString voffset_text;

	static constexpr int slider_int=400;
	static constexpr qreal angle_def=2.0;
	static constexpr qreal hoffset_def=0.0;
	static constexpr qreal voffset_def=0.0;
};

#endif // CONSTANTS_H
