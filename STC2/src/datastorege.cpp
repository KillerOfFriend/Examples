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
bool DataStorege::setData(const quint64 inRow, const CustomColumns inCol, const QVariant& inData, bool inUpdateModel)
{
    bool Result = false;

     if (inRow < mData.size() && inCol < CustomColumns::ccCount) // Существуюая строка
     {
         Result = true;
         std::lock_guard<std::mutex> lg(mDataDefender);

         if (inUpdateModel)
            sig_onStartRestart();

         switch (inCol)
         {
             case CustomColumns::ccID:       { mData[inRow].mID = inData.toUInt(); break; }
             case CustomColumns::ccName:     { mData[inRow].mName = inData.toString(); break; }
             case CustomColumns::ccTelefon:  { mData[inRow].mTelefon = inData.toUInt(); break; }
             case CustomColumns::ccCountry:  { mData[inRow].mCountryCode = static_cast<eCountry>(inData.toInt()); break; }

             default:                        { Result = false; break; }
         }

         if (inUpdateModel)
            sig_onEndRestart();

         if (Result)
            sig_onSetData(inRow, inCol, inData);
     }

     return Result;
}
//-----------------------------------------------------------------------------
bool DataStorege::insertRow(const quint64 inRow, bool inUpdateModel)
{
    bool Result = false;

    if (inRow > mData.size())
        Result = false;
    else
    {
        Result = true;

        {
            std::lock_guard<std::mutex> lg(mDataDefender);

            if (inUpdateModel)
               sig_onStartRestart();

            // Формируем данные с уникальным идентификатором
            CustomData NewRowData;

            if (mData.empty())
                NewRowData.mID = 1;
            else
            {
                auto FindRes = std::max_element(mData.cbegin(), mData.cend(), [](const CustomData& Item1, const CustomData& Item2)
                { return Item1.mID < Item2.mID; });

                 NewRowData.mID = FindRes->mID + 1;
            }

            auto Pos = mData.begin();
            std::advance(Pos, inRow);
            mData.insert(Pos, NewRowData);

            if (inUpdateModel)
               sig_onEndRestart();
        }

        sig_onInsertRow(inRow);
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool DataStorege::removeRow(const quint64 inRow, bool inUpdateModel)
{
    bool Result = false;

    if (inRow < mData.size())
    {
        Result = true;

        {
            std::lock_guard<std::mutex> lg(mDataDefender);

            if (inUpdateModel)
               sig_onStartRestart();

            auto Pos = mData.begin();
            std::advance(Pos, inRow);
            mData.erase(Pos);

            if (inUpdateModel)
               sig_onEndRestart();
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
