#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <vector>
#include <mutex>

#include <asio.hpp>

#include "observer.h"
#include "serverconnection.h"

//-----------------------------------------------------------------------------
class Server : public Subscriber, public std::enable_shared_from_this<Server>
{
public:

    Server();
    virtual ~Server() override;


    bool start();
    void stop();
    bool isStarted() const;

    /**
     * @brief update - Метод обработает событие от паблишера
     * @param inPublisher - Инициатор события
     * @param inEvent - Код события
     */
    virtual void update(std::shared_ptr<Publisher> inPublisher, std::uint32_t inEvent) override;

private:

    bool m_IsStarted = false;
    std::thread m_WorkThread; ///< Рабочий поток прослушки порта

    asio::io_service m_Service; ///< Сервис обработки соединений
    std::unique_ptr<asio::ip::tcp::acceptor> m_Acceptor = nullptr; ///< Объект, подтверждающий соединения

    std::vector<std::shared_ptr<ServerConnection>> m_Connections;
    std::mutex m_ConnectionsDefender;

    /**
     * @brief handle_accept - Обработчик подключения
     * @param inClient - Подключаемый клиент
     * @param inError - Признак ошибки
     */
    void handle_accept(std::shared_ptr<ServerConnection> inClient, const std::error_code& inError);
};
//-----------------------------------------------------------------------------

#endif // SERVER_H
