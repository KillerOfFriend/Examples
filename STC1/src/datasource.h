#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include <QObject>
#include <QVariant>

#include "types.h"

//-----------------------------------------------------------------------------
/**
 * @brief The iDataSource class - Интерфейс источника данных
 */
class iDataSource : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief iDataSource - Конструктор по умолчанию
     * @param inParent - Родительский объект
     */
    iDataSource(QObject *inParent = nullptr);

    /**
     * @brief ~iDataSource - Виртуальный деструкторр по умолчанию
     */
    virtual ~iDataSource() = default;

    /**
     * @brief rowCount - Метод вернёт количество хранимых записей
     * @return Вернёт количество хранимых записей
     */
    virtual std::size_t rowCount() const = 0;

    /**
     * @brief getData - Метод вернёт данные по указанным "кординатам"
     * @param inRow - Строка
     * @param inCol - Столбец
     * @return Вернёт данные или не валидный QVariant
     */
    virtual QVariant getData(const std::size_t inRow, const CustomColumns inCol) = 0;

    /**
     * @brief setData - Метод обновит данные по указанным "кординатам"
     * @param inRow - Строка
     * @param inCol - Столбец
     * @param inData - Новое значение данных
     * @return Вернёт признак успешности операции
     */
    virtual bool setData(const std::size_t inRow, const CustomColumns inCol, const QVariant& inData) = 0;

    /**
     * @brief removeData - Метод удалит данные поуказанным координатам
     * @param inRow - Строка
     * @return Вернёт признак успешности операции
     */
    virtual bool removeData(const std::size_t inRow) = 0;

    /**
     * @brief update - Метод перезагрузит данные
     * @return Вернёт признак успешности операции
     */
    virtual bool update() = 0;

    /**
     * @brief upload - Метод выгрузит данные
     * @return Вернёт признак успешности операции
     */
    virtual bool upload() = 0;

signals:

    /**
     * @brief sig_onError - Сигнал, сообщающий что опроизошла ошибка
     * @param inErrMessage - Сообщение об ошибке
     */
    void sig_onError(QString inErrMessage);

    /**
     * @brief sig_onUpdateProc - Сигнал, сообщающий состояние процесса обновления данных
     * @param inPos - Текущая позиция
     * @param inMax - Максимальная позиция
     */
    void sig_onUpdateProc(int inPos, int inMax);

};
//-----------------------------------------------------------------------------

#endif // IDATASOURCE_H
