#include "server.h"

#include <iostream>
#include <functional>

using namespace std::placeholders;

//-----------------------------------------------------------------------------
Server::Server() : Subscriber()
{

}
//-----------------------------------------------------------------------------
Server::~Server()
{
    stop();
}
//-----------------------------------------------------------------------------
bool Server::start()
{
    if (!isStarted()) // Если сервер не запущен
    {
        try
        {
            m_Acceptor = std::make_unique<asio::ip::tcp::acceptor>(m_Service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8564));

            // Реализуем функцию подтверждения соединения
            auto AcceptFunc = [this](std::shared_ptr<ServerConnection> client, const std::error_code& error)
            { this->handle_accept(client, error); };

            std::shared_ptr<ServerConnection> NewConnection = std::make_shared<ServerConnection>(m_Service);
            NewConnection->subscribe(shared_from_this());
            m_Acceptor->async_accept(NewConnection->socket(), std::bind(AcceptFunc, NewConnection, _1)); // Задаём серверу функцию подтверждения
            {
                std::lock_guard<std::mutex> lg(m_ConnectionsDefender);
                m_Connections.push_back(NewConnection);
            }

            m_WorkThread = std::thread([this]()
            {
                m_Service.reset();
                m_Service.restart();
                asio::io_service::work RunForever(m_Service); // ДЛЯ ДОСТУПНОСТИ СЕССИИ
                m_Service.run();
            }); // Запускаем сервис в отдельном потоке

            m_IsStarted = m_WorkThread.joinable();;
        }
        catch (const std::exception& Except)
        {
            std::cerr << Except.what() << std::endl;
        }
    }

    return isStarted();
}
//-----------------------------------------------------------------------------
void Server::stop()
{
    if (isStarted())
    {
        m_Service.stop();

        if (m_WorkThread.joinable())
            m_WorkThread.join();

        m_IsStarted = false;
    }
}
//-----------------------------------------------------------------------------
bool Server::isStarted() const
{ return m_IsStarted; }
//-----------------------------------------------------------------------------
void Server::update(std::shared_ptr<Publisher> inPublisher, std::uint32_t inEvent)
{
    std::lock_guard<std::mutex> lg(m_ConnectionsDefender);

    switch (inEvent)
    {
        case cEventDisconnect:
        {
            auto FindRes = std::find(m_Connections.begin(), m_Connections.end(), inPublisher);

            if (FindRes != m_Connections.end())
                m_Connections.erase(FindRes);

            break;
        }


        default: break;
    }
}
//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
void Server::handle_accept(std::shared_ptr<ServerConnection> inClient, const std::error_code& inError)
{
    if (inError)
        std::cerr << inError.message() << std::endl;
    else
    {
        inClient->connect(); // Запускаем соединение

        // Реализуем функцию подтверждения соединения
        auto AcceptFunc = [this](std::shared_ptr<ServerConnection> client, const std::error_code& error)
        { this->handle_accept(client, error); };

        std::shared_ptr<ServerConnection> NewConnection = std::make_shared<ServerConnection>(m_Service);
        NewConnection->subscribe(shared_from_this());
        m_Acceptor->async_accept(NewConnection->socket(), std::bind(AcceptFunc, NewConnection, _1)); // Задаём соединению функцию подтверждения

        std::lock_guard<std::mutex> lg(m_ConnectionsDefender);
        m_Connections.push_back(NewConnection);
    }
}
//-----------------------------------------------------------------------------
