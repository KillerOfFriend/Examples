#include "datastorege.h"

#include "tools.h"

//-----------------------------------------------------------------------------
DataStorege::DataStorege(QObject *inParent) : QObject(inParent)
{

}
//-----------------------------------------------------------------------------
void DataStorege::init(const std::vector<CustomData>& inData)
{
    std::lock_guard<std::mutex> lg(mDataDefender);
    sig_onStartRestart();
    mData = inData;
    sig_onEndRestart();
}
//-----------------------------------------------------------------------------
quint64 DataStorege::getRowCount() const
{
    return mData.size();
}
//-----------------------------------------------------------------------------
QVariant DataStorege::getData(const quint64 inRow, const CustomColumns inCol) const
{
    QVariant Result = {};

    if (inRow < mData.size() && inCol < CustomColumns::ccCount)
    {
        std::lock_guard<std::mutex> lg(mDataDefender);

        switch (inCol)
        {
            case CustomColumns::ccID:       { Result = mData[inRow].mID; break; }
            case CustomColumns::ccName:     { Result = mData[inRow].mName; break; }
            case CustomColumns::ccTelefon:  { Result = mData[inRow].mTelefon; break; }
            case CustomColumns::ccCountry:  { Result = tools::countryText(mData[inRow].mCountryCode); break; }

            default:                        { Result = QVariant(); break; }
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool DataStorege::setData(const quint64 inRow, const CustomColumns inCol, const QVariant& inData)
{
    bool Result = false;

     if (inRow < mData.size() && inCol < CustomColumns::ccCount) // Существуюая строка
     {
         Result = true;
         std::lock_guard<std::mutex> lg(mDataDefender);

         switch (inCol)
         {
             case CustomColumns::ccID:       { mData[inRow].mID = inData.toUInt(); break; }
             case CustomColumns::ccName:     { mData[inRow].mName = inData.toString(); break; }
             case CustomColumns::ccTelefon:  { mData[inRow].mTelefon = inData.toUInt(); break; }
             case CustomColumns::ccCountry:  { mData[inRow].mCountryCode = static_cast<eCountry>(inData.toInt()); break; }

             default:                        { Result = false; break; }
         }

         if (Result)
            sig_onSetData(inRow, inCol, inData);
     }

     return Result;
}
//-----------------------------------------------------------------------------
bool DataStorege::insertRow(const quint64 inRow)
{
    bool Result = false;

    if (inRow > mData.size())
        Result = false;
    else
    {
        Result = true;

        {
            std::lock_guard<std::mutex> lg(mDataDefender);

            auto Pos = mData.begin();
            std::advance(Pos, inRow);
            mData.insert(Pos, CustomData());
        }

        sig_onInsertRow(inRow);
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool DataStorege::removeRow(const quint64 inRow)
{
    bool Result = false;

    if (inRow < mData.size())
    {
        {
            std::lock_guard<std::mutex> lg(mDataDefender);

            auto Pos = mData.begin();
            std::advance(Pos, inRow);
            mData.erase(Pos);
        }

        sig_onRemoveRow(inRow);
    }

    return Result;
}
//-----------------------------------------------------------------------------
std::vector<CustomData> DataStorege::dump() const
{
    std::lock_guard<std::mutex> lg(mDataDefender);
    return mData;
}
//-----------------------------------------------------------------------------
