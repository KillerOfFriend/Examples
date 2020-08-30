#ifndef SQLITE_H
#define SQLITE_H

#include <vector>

#include <QSqlDatabase>
#include <QString>

#include "types.h"

//-----------------------------------------------------------------------------
class SqLite
{
public:

    SqLite(const QString inDbFileName, const QString inDbConnectionName);
    ~SqLite() = default;

    /**
     * @brief loadFromDB - Метод загрузит данные из БД
     * @return Вернёт перечень загруженых данных
     */
    std::vector<CustomData> loadFromDB() const;

    /**
     * @brief saveToDB - Метод выгрузит данные в БД
     * @param inData - Перечень выгружаемых данных
     * @return Вернёт признак успешности операции
     */
    bool saveToDB(const std::vector<CustomData>& inData) const;

private:

    const QString mDbFileName; ///< Имя файла БД
    const QString mDbConnectionName; ///< Имя соединения БД

    /**
     * @brief getDataBaseConnection - Метод вернёт соединение с БД
     * @return Вернёт соединение с БД
     */
    QSqlDatabase getDataBaseConnection() const;

    /**
     * @brief createDbTable - Метод создасть таблицу в БД
     * @return Вернёт признак успешности операции
     */
    bool createDbTable() const;

    /**
     * @brief initDbTable - Метод инициализирует таблицу бд если необходимо
     * @return Вернёт признак успешности операции
     */
    bool initDbTable() const;

    /**
     * @brief removeIfNead - Метод удалит из бд удалённые записи
     * @param inData - Текушее состояние датасета
     */
    void removeIfNead(const std::vector<CustomData>& inData) const;

};
//-----------------------------------------------------------------------------

#endif // SQLITE_H
