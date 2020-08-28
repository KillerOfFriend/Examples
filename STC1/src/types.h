#ifndef TYPES_H
#define TYPES_H

#include <QString>

//-----------------------------------------------------------------------------
/**
 * @brief The CustomColumns enum - Перечень столбцов
 */
enum CustomColumns : quint8
{
    ccTextEditor = 0,
    ccFileFormats = 1,
    ccEncoding = 2,
    ccHasIntelLisense = 3,
    ccHasPlugin = 4,
    ccCanCompile = 5,

    ccCount
};
//-----------------------------------------------------------------------------
/**
 * @brief The CustomData struct - Структура описывает одну запись
 */
struct CustomData
{
    bool mHasPlugin = false;
    bool mCanCompile = false;
    bool mHasIntelLisense = false;
    QString mTextEditor = "-----";
    QString mFileFormats = "-----";
    QString mEncoding = "-----";
};
//-----------------------------------------------------------------------------

#endif // TYPES_H
