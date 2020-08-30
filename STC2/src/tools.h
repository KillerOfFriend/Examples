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

//-----------------------------------------------------------------------------
// enum streams
//-----------------------------------------------------------------------------
template<class T, typename std::enable_if<std::is_enum<T>::value, T>::type* = nullptr>
QDataStream &operator<<(QDataStream& stream, const T &enumValue)
{
    return stream << static_cast<std::underlying_type_t<T>>(enumValue);
}
//-----------------------------------------------------------------------------
template<class T, typename std::enable_if<std::is_enum<T>::value, T>::type* = nullptr>
QDataStream &operator>>(QDataStream& stream, T &enumValue)
{
    std::underlying_type_t<T> val;
    stream >> val;
    enumValue = static_cast<T>(val);
    return stream;
}
//-----------------------------------------------------------------------------
QDataStream &operator << (QDataStream &outStream, const CustomData& Data);
//-----------------------------------------------------------------------------
QDataStream &operator >> (QDataStream &inStream, CustomData& Data);
//-----------------------------------------------------------------------------

#endif // TOOLS_H
