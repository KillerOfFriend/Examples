#ifndef TOOLS_H
#define TOOLS_H

#include <QString>

#include "types.h"

namespace tools
{

//-----------------------------------------------------------------------------
/**
 * @brief countryText - Функция вернёт название страны по её коду
 * @param inCountyCode - Код страны
 * @return Вернёт название страны
 */
QString countryText(const eCountry inCountyCode);
//-----------------------------------------------------------------------------

}



#endif // TOOLS_H
