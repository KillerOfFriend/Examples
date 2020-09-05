#ifndef ABSTRACTCONNECTION_H
#define ABSTRACTCONNECTION_H

#include <asio.hpp>

#include "observer.h"

static const std::uint8_t cEventDisconnect = 1;

//-----------------------------------------------------------------------------
/*!
 * @brief The ServerConnection class - Класс, описывающий абстрактное соединение
 */
class ServerConnection : public Publisher, asio::noncopyable
{
public:

    /*!
     * @brief ServerConnection - Инициализирующий конструктор
     * @param inService - Рабочий сервис
     */
    ServerConnection(asio::io_service& inService);

    /*!
     * @brief ~ServerConnection - Деструктор
     */
    virtual ~ServerConnection(); // Деструктор

    /*!
     * @brief connect - Метод запустит соединение
     */
    void connect();

    /*!
     * @brief disconnect - Метод разорвёт соединение
     */
    void disconnect();

    /*!
     * @brief isConnected - Метод вернёт состояние соединения
     * @return Вернёт состояние соединения
     */
    bool isConnected() const;

    /**
     * @brief socket - Метод вернёт ссылку на сокет
     * @return Вернёт ссылку на сокет
     */
    asio::ip::tcp::socket& socket();

    /*!
     * @brief localEndPoint - Метод вернёт локальные данные соединения
     * @return Вернёт локальные данные соединения
     */
    asio::ip::tcp::endpoint localEndPoint() const;

    /*!
     * @brief remoteEndPoint - Метод вернёт удалённые данные соединения
     * @return Вернёт удалённые данные соединения
     */
    asio::ip::tcp::endpoint remoteEndPoint() const;


protected:

    asio::ip::tcp::socket m_Socket;      ///< Сокет
    std::uint64_t m_MaxBufferSize = 0;   ///< Максимальный размер буфера

    /*!
     * @brief readNext - Метод продолжит чтение
     */
    void readNext();

    /*!
     * @brief writeNext - Метод продолжит запись
     */
    void writeNext();

    /*!
     * @brief ServerConnection::onDisconnect - Событие после разрыва соединения
     */
    virtual void onDisconnect();

private:

    bool m_IsConnected = false; ///< Флаг состояния соединния
    asio::io_service& m_Service; ///< Рабочий сервис соединения

    std::string m_readBuffer;       ///< Буфер чтения
    std::string m_writeBuffer;      ///< Буфер записи

    /*!
     * @brief read - Метод чтения из сокета
     */
    void read();

    /*!
     * @brief write - Метод записи в сокет
     */
    void write();

    /*!
     * @brief readData - Метод считывающий порцию данных
     * @param inSize - Размер полученой порции данных
     */
    void readData(const std::uint64_t inSize);

    // Обработчики

    /*!
     * @brief ServerConnection::onRead - Событие по завершению чтения из сокета
     * @param inError - Признак ошибки
     * @param inBytes - Количество считанных байт
     */
    void onRead(const std::error_code &inError, const std::uint64_t inBytes);

    /*!
     * @brief ServerConnection::onWrite - Событие по завершению записи в сокет
     * @param inError - Признак ошибки
     * @param inBytes - Количество записанных байт
     */
    void onWrite(const std::error_code &inError, const std::uint64_t inBytes);


};
//-----------------------------------------------------------------------------

#endif // ABSTRACTCONNECTION_H
