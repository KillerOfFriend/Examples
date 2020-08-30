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





//-----------------------------------------------------------------------------
QDataStream &operator << (QDataStream &outStream, const CustomData& Data)
{
    outStream << Data.mID;
    outStream << Data.mName;
    outStream << Data.mTelefon;
    outStream << Data.mCountryCode;

   return outStream;
}
//-----------------------------------------------------------------------------
QDataStream &operator >> (QDataStream &inStream, CustomData& Data)
{
    inStream >> Data.mID;
    inStream >> Data.mName;
    inStream >> Data.mTelefon;
    inStream >> Data.mCountryCode;

   return inStream;
}
//-----------------------------------------------------------------------------
