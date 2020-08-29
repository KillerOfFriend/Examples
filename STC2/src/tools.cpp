#include "tools.h"

#include <QObject>

//-----------------------------------------------------------------------------
QString tools::countryText(const eCountry inCountyCode)
{
    QString Result;

    switch (inCountyCode)
    {
        case eCountry::cUSA:        { Result = QObject::tr("США"); break; }
        case eCountry::cRussia:     { Result = QObject::tr("Россия"); break; }
        case eCountry::cUkraine:    { Result = QObject::tr("Украина"); break; }

        default:                    { Result = QObject::tr("Не определена"); break; }
    }

    return Result;
}
//-----------------------------------------------------------------------------
