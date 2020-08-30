#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QDataStream>

//-----------------------------------------------------------------------------
/**
 * @brief The eCountry enum - Перечень стран
 */
enum eCountry
{
    cUSA = 1,
    cRussia = 8,
    cUkraine = 38
};
//-----------------------------------------------------------------------------
/**
 * @brief The CustomColumns enum - Перечень столбцов
 */
enum CustomColumns
{
    ccID = 0,
    ccName = 1,
    ccTelefon = 2,
    ccCountry = 3,

    ccCount
};
//-----------------------------------------------------------------------------
/**
 * @brief The CustomData struct - Структура описывает одну запись
 */
struct CustomData
{
    quint32 mID = 0;
    QString mName = {};
    quint64 mTelefon = 0;
    eCountry mCountryCode;
};
//-----------------------------------------------------------------------------

#endif // TYPES_H
