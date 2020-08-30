#ifndef NETWORK_H
#define NETWORK_H

#include <memory>

#include <QObject>
#include <QByteArray>

#include "datastorege.h"

//-----------------------------------------------------------------------------
/**
 * @brief The ePackageType enum - Перечень типов передаваемых пакетов
 */
enum ePackageType //: quint8
{
    ptInit = 1,
    ptEdit = 2,
    ptInsert = 3,
    ptRemove = 4
};
//-----------------------------------------------------------------------------
/**
 * @brief The NetWork class - Класс описывает абстракцию сетевой работы
 */
class NetWork : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief NetWork - Инициализирующий конструктор
     * @param inDataStorege - Указатель на хранилище данных
     * @param inParent - Объект-предок
     */
    NetWork(const std::shared_ptr<DataStorege> inDataStorege, QObject* inParent = nullptr);

    /**
     * @brief ~NetWork - Виртуальный деструктор по умолчанию
     */
    virtual ~NetWork() override = default;

    /**
     * @brief start - Метод запусти соединение
     * @return Вернёт признак успешности операции
     */
    virtual bool start() = 0;

    /**
     * @brief stop - Метод остановит соединение
     */
    virtual void stop() = 0;

protected:
    std::shared_ptr<DataStorege> mDataStorege = nullptr; ///< Хранилище данных

    /**
     * @brief write - Метод отправит данные по сокету
     * @param inData - Отправляемые данные
     */
    virtual void write(const QByteArray inData) = 0;

    /**
     * @brief read - Метод примит данные из сокета
     * @param inData - Полученные данные
     */
    virtual void read(QByteArray inData);

    /**
     * @brief onInit - Метод обработает запрос инициализации
     * @param inInitData - Данные инициализации
     */
    virtual void onInit(QByteArray inInitData) = 0;

    /**
     * @brief connectDataStorege - Метод подключит сигналы хранилища
     */
    void connectDataStorege();

    /**
     * @brief disconnectDataStorege - Метод отключит сигналы хранилища
     */
    void disconnectDataStorege();

private slots:

    /**
     * @brief slot_onSetData - Слот, реагирующий на изменение данных
     * @param inRow - Строка
     * @param inCol - Столбец
     * @param inData - Новые данные
     */
    void slot_onSetData(quint64 inRow, CustomColumns inCol, QVariant inData);

    /**
     * @brief slot_onInsertRow - Слот, реагирующий на добовление троки
     * @param inRow - Строка
     */
    void slot_onInsertRow(quint64 inRow);

    /**
     * @brief slot_onRemoveRow - Слот, реагирующий на удаление строки
     * @param inRow - Строка
     */
    void slot_onRemoveRow(quint64 inRow);

};
//-----------------------------------------------------------------------------

#endif // NETWORK_H
