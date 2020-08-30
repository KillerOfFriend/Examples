#include "sqlite.h"

#include <algorithm>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "constants.h"

//-----------------------------------------------------------------------------
SqLite::SqLite(const QString inDbFileName, const QString inDbConnectionName)
    : mDbFileName(inDbFileName),
      mDbConnectionName(inDbConnectionName)
{

}
//-----------------------------------------------------------------------------
std::vector<CustomData> SqLite::loadFromDB() const
{
    if (createDbTable())
        initDbTable();

    std::vector<CustomData> Result;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
        qDebug() << DB.lastError();
    else
    {
        QSqlQuery Query(DB);

        if (!Query.exec("SELECT * FROM CustomData"))
            qDebug() << Query.lastError();
        else
        {
            while (Query.next())
            {
                CustomData NewData;

                NewData.mID = Query.value(cID).toUInt();
                NewData.mName = Query.value(cName).toString();
                NewData.mTelefon = Query.value(cPhone).toULongLong();
                NewData.mCountryCode = static_cast<eCountry>(Query.value(cCounty).toInt());

                Result.push_back(NewData);
            }
        }

        DB.close();
    }

    return std::move(Result);
}
//-----------------------------------------------------------------------------
bool SqLite::saveToDB(const std::vector<CustomData> &inData) const
{
    removeIfNead(inData);

    bool Result = false;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
    {
        Result = false;
        qDebug() << DB.lastError();
    }
    else
    {
        QSqlQuery Query(DB);

        for (const auto& Row : inData)
        {
            Query.prepare("INSERT OR REPLACE INTO CustomData ("
                            "" + cID + ", "
                            "" + cName + ", "
                            "" + cPhone + ", "
                            "" + cCounty + ""
                            " ) VALUES ( "
                            ":" + cID + ", "
                            ":" + cName + ", "
                            ":" + cPhone + ", "
                            ":" + cCounty + " )");

            Query.bindValue(":" + cID, Row.mID);
            Query.bindValue(":" + cName, Row.mName);
            Query.bindValue(":" + cPhone, Row.mTelefon);
            Query.bindValue(":" + cCounty, Row.mCountryCode);

            if (!Query.exec())
                qDebug() << Query.lastError();
        }

        DB.close();
        Result = true;
    }

    return Result;
}
//-----------------------------------------------------------------------------
QSqlDatabase SqLite::getDataBaseConnection() const
{
    QSqlDatabase DB;

    if (!QSqlDatabase::contains(mDbConnectionName))
    {
        DB = QSqlDatabase::addDatabase("QSQLITE", mDbConnectionName);
        DB.setDatabaseName(mDbFileName);
        DB.open();
    }
    else
        DB = QSqlDatabase::database(mDbConnectionName, true);


    return std::move(DB);
}
//-----------------------------------------------------------------------------
bool SqLite::createDbTable() const
{
    bool Result = false;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
    {
        Result = false;
        qDebug() << DB.lastError();
    }
    else
    {
        QString QueryText = "CREATE TABLE IF NOT EXISTS CustomData ("
                            "" + cID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                            "" + cName + " VARCHAR(50) NOT NULL, "
                            "" + cPhone + " UNSIGNED BIG INT NOT NULL, "
                            "" + cCounty + " INTEGER NOT NULL)";

        QSqlQuery Query(DB);
        Result = Query.exec(QueryText);
        DB.close();
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool SqLite::initDbTable() const
{
    bool Result = false;
    QSqlDatabase DB = getDataBaseConnection();

    if (!DB.isOpen())
    {
        Result = false;
        qDebug() << DB.lastError();
    }
    else
    {
        QSqlQuery Query(DB);

        if (!Query.exec("SELECT COUNT(*) FROM CustomData"))
        {
            Result = false;
            qDebug() << Query.lastError();
        }
        else
        {
            Query.next();

            if (Query.value(0).toInt() != 0)
                Result = false;
            else
            {
                Query.prepare("INSERT INTO CustomData VALUES ("
                            ":" + cID + ", "
                            ":" + cName + ", "
                            ":" + cPhone + ", "
                            ":" + cCounty + ")");

                QVariantList IDs, Name, Phone, Country;

                IDs     << 1                    << 2                    << 3                    << 4                    << 5                    << 6;
                Name    << "Осип"               << "Розалина"           << "Виталий"            << "Валерия"            << "Евгений"            << "Людмила";
                Phone   << quint64(8384201433)  << quint64(85540729804) << quint64(85175119904) << quint64(85155921468) << quint64(84041925532) << quint64(89463735992);
                Country << cUSA                 << cRussia              << cUkraine             << cUSA                 << cRussia              << cUkraine;

                Query.addBindValue(IDs);
                Query.addBindValue(Name);
                Query.addBindValue(Phone);
                Query.addBindValue(Country);


                Result = Query.execBatch();
                if (!Result)
                    qDebug() << Query.lastError();
            }
        }
        DB.close();
    }

    return Result;
}
//-----------------------------------------------------------------------------
void SqLite::removeIfNead(const std::vector<CustomData>& inData) const
{
    std::vector<CustomData> DbData = loadFromDB();
    std::vector<CustomData> Res;

    // Ищим разницу между состоянием бд и текущим датасетом

    std::set_difference(DbData.cbegin(), DbData.cend(), inData.cbegin(), inData.cend(), std::back_inserter(Res), [](const CustomData& Item1, const CustomData& Item2)
    {
        return Item1.mID < Item2.mID;
    });

    if (!Res.empty())
    {
        QSqlDatabase DB = getDataBaseConnection();

        if (!DB.isOpen())
            qDebug() << DB.lastError();
        else
        {
            QSqlQuery Query(DB);

            QStringList Keys;
            for (const CustomData& Item : Res)
                Keys << QString::number(Item.mID);

            Query.prepare("DELETE FROM CustomData WHERE " + cID + " IN ( :IDs )");
            Query.bindValue(":keys", Keys.join(", "));

            if (!Query.exec())
                qDebug() << Query.lastError();

            DB.close();
        }
    }
}
//-----------------------------------------------------------------------------
