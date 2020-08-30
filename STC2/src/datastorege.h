#ifndef DATASTOREGE_H
#define DATASTOREGE_H

#include <vector>
#include <mutex>

#include <QVariant>
#include <QObject>

#include "types.h"

//-----------------------------------------------------------------------------
/**
 * @brief The DataStorege class - Класс, описывающий хранилище данных
 */
class DataStorege : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief DataStorege - Инициализирующий конструктор
     * @param inParent - Родительский объект
     */
    DataStorege(QObject *inParent = nullptr);

    /**
     * @brief ~DataStorege - Деструктор по умолчанию
     */
    ~DataStorege() = default;

    /**
     * @brief init - Метод инициализирует данные
     * @param inData - Новые данные
     */
    void init(const std::vector<CustomData>& inData);

    /**
     * @brief getRowCount - Метод вернёт количество строк
     * @return Вернёт количество строк
     */
    quint64 getRowCount() const;

    /**
     * @brief getData - Метод вернёт данные по указанным координатами
     * @param inRow - Строка
     * @param inCol - Столбец
     * @return Вернёт данные по указанным координатами
     */
    QVariant getData(const quint64 inRow, const CustomColumns inCol) const;

    /**
     * @brief setData - Метод задаст данные по указанным координатам
     * @param inRow - Строка
     * @param inCol - Столбец
     * @param inData - Новые данные
     * @return Вернёт признак успешности операции
     */
    bool setData(const quint64 inRow, const CustomColumns inCol, const QVariant& inData);

    /**
     * @brief insertRow - Метод вставит пустую строку
     * @param inRow - Строка
     * @return Вернёт признак успешности операции
     */
    bool insertRow(const quint64 inRow);

    /**
     * @brief removeRow - Метод удалит строку
     * @param inRow - Строка
     * @return Вернёт признак успешности операции
     */
    bool removeRow(const quint64 inRow);

    /**
     * @brief dump - Метод вернёт копию сожержимого хранилища данных
     * @return Вернёт копию сожержимого хранилища данных
     */
    std::vector<CustomData> dump() const;

private:

    std::vector<CustomData> mData;      ///< Котнтейнер данных
    mutable std::mutex mDataDefender;   ///< Мьютекс, защищающий данные

signals:

    // Сигналы для сети

    /**
     * @brief sig_onSetData - Сигнал, возникающий при модификации данных строки
     * @param inRow - Строка
     * @param inCol - Столбец
     * @param inData - Модифицированные данные
     */
    void sig_onSetData(quint64 inRow, CustomColumns inCol, QVariant inData);

    /**
     * @brief sig_onInsertRow - Сигнал, возникающий при вставке новой строки
     * @param inRow - Строка
     */
    void sig_onInsertRow(quint64 inRow);

    /**
     * @brief sig_onRemoveRow - Сигнал, возникающий при удалении строки
     * @param inRow - Строка
     */
    void sig_onRemoveRow(quint64 inRow);

    // Сигналы для модели

    /**
     * @brief sigStartRestart - Сигнал, возникающий в начале обновления данных
     */
    void sig_onStartRestart();

    /**
     * @brief sigEndRestart - Сигнал, возникающий в конце обновления данных
     */
    void sig_onEndRestart();

};
//-----------------------------------------------------------------------------


#endif // DATASTOREGE_H
