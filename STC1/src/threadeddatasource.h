#ifndef ATHREADEDDATASOURCE_H
#define ATHREADEDDATASOURCE_H

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

#include "datasource.h"

//-----------------------------------------------------------------------------
struct BaseData
{
    BaseData() = default;
    BaseData(const CustomData& inData) : mData(inData) {}
    virtual ~BaseData() = default;

    CustomData mData;           ///< Данные
    bool mDataModified = false; ///< Флаг модификации данных
};
//-----------------------------------------------------------------------------
class aThreadedDataSource : public iDataSource
{
public:

    /**
     * @brief aThreadedDataSource - Инициализирующий конструктор
     * @param inParent - Объект-предок
     */
    aThreadedDataSource(QObject *inParent = nullptr);

    /**
     * @brief ~aThreadedDataSource - Виртуальный деструктор
     */
    virtual ~aThreadedDataSource() override;

    /**
     * @brief rowCount - Метод вернёт количество хранимых записей
     * @return Вернёт количество хранимых записей
     */
    virtual std::size_t rowCount() const override;

    /**
     * @brief getData - Метод вернёт данные по указанным "кординатам"
     * @param inRow - Строка
     * @param inCol - Столбец
     * @return Вернёт данные или не валидный QVariant
     */
    virtual QVariant getData(const std::size_t inRow, const CustomColumns inCol) override;

    /**
     * @brief setData - Метод обновит данные по указанным "кординатам"
     * @param inRow - Строка
     * @param inCol - Столбец
     * @param inData - Новое значение данных
     * @return Вернёт признак успешности операции
     */
    virtual bool setData(const std::size_t inRow, const CustomColumns inCol, const QVariant& inData) override;

    /**
     * @brief removeData - Метод удалит данные поуказанным координатам
     * @param inRow - Строка
     * @return Вернёт признак успешности операции
     */
    virtual bool removeData(const std::size_t inRow) override;

    /**
     * @brief update - Метод перезагрузит данные
     * @return Вернёт признак успешности операции
     */
    virtual bool update() override;

    /**
     * @brief upload - Метод выгрузит данные
     * @return Вернёт признак успешности операции
     */
    virtual bool upload() override;

protected:

    std::vector<std::shared_ptr<BaseData>> mDataStorage;    ///< Обрабатываемые данные
    std::mutex mDataDefender;       ///< Мьютекс, защищающий хранилище данных

    /**
     * @brief updateInThread - Метод загрузки данных, выполняемый в отдельном потоке
     */
    virtual void updateInThread() = 0;

    /**
     * @brief uploadInThread - Метод выгрузки данных, выполняемый в отдельном потоке
     */
    virtual void uploadInThread() = 0;

private:

    std::thread mReadThread;        ///< Поток чтения
    std::thread mWriteThread;       ///< Поток записи
    std::atomic_bool mIsReading;    ///< Флаг "Идёт чтение"
    std::atomic_bool mIsWriteing;   ///< Флаг "Идёт запись"

    /**
     * @brief startUpdateInThread - Метод запустит загрузку в потоке
     */
    void startUpdateInThread();

    /**
     * @brief startUploadInThread - Метод запустит выгрузку в потоке
     */
    void startUploadInThread();

};
//-----------------------------------------------------------------------------

#endif // ATHREADEDDATASOURCE_H
