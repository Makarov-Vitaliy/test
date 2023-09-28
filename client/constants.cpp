#include "constants.h"

//Q_GLOBAL_STATIC
const QStringList Constants::light_theme = {"Красный","Черный"};
const QStringList Constants::dark_theme = {"Красный"};
const QMap<QString,QStringList> Constants::colors_map = {{"Черный",Constants::dark_theme},
                                                         {"Белый",Constants::light_theme},
                                                         {"Серый",Constants::light_theme}
                                                        };

Constants::Constants()
{

}

