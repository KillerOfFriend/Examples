#ifndef DBDATASOURCE_H
#define DBDATASOURCE_H

#include <vector>
#include <thread>
#include <mutex>

#include <QSqlDatabase>

#include "threadeddatasource.h"
#include "types.h"

//-----------------------------------------------------------------------------
/**
 * @brief The DbRow struct - Информация о строкие
 */
struct RowData : public BaseData
{
    RowData(const std::size_t inIndex) : mIndex(inIndex) {}
    virtual ~RowData() override = default;

    std::size_t mIndex = 0; ///< Индекс строки
};
//-----------------------------------------------------------------------------
/**
 * @brief The DBDataSource class - Класс, описывает источник данных из БД
 */
class DBDataSource : public aThreadedDataSource
{
public:
    DBDataSource(const QString& inDbFilePath, QObject *inParent = nullptr);

    /**
     * @brief ~DBDataSource - Виртуальный деструкторр
     */
    virtual ~DBDataSource() override;

private:

    QSqlDatabase mDataBase;         ///< Соединение с БД

    /**
     * @brief updateInThread - Метод загрузки данных, выполняемый в отдельном потоке
     */
    void updateInThread();

    /**
     * @brief uploadInThread - Метод выгрузки данных, выполняемый в отдельном потоке
     */
    void uploadInThread();

    /**
     * @brief createTable - Метод создаст таблицу в БД если её не существует
     * @return Вернёт признак успешности операции
     */
    bool createTable() const;

    /**
     * @brief initTable - Метод заполнит таблицу если в ней ничего нет
     */
    void initTable() const;

    /**
     * @brief checkParams - Сетод проверит наличие всех параметров после разбора
     * @param inQueryRes - Результат запроса
     * @return Вернёт признак ошибки
     */
    std::error_code checkParams(const QSqlQuery& inQueryRes) const;

    /**
    * @brief writeRow - Метод запишет изменённую строку в БД
    * @param inIndex - Индекс записи
    * @param inData - Записываемые данные
    * @return Вернёт признак ошибки
    */
   std::error_code writeRow(const std::size_t inIndex, const CustomData& inData);

};
//-----------------------------------------------------------------------------

#endif // DBDATASOURCE_H
