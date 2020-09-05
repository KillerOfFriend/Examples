#include "serverconnection.h"

#include <random>
#include <iostream>
#include <functional>

//-----------------------------------------------------------------------------
using namespace std::placeholders;
//-----------------------------------------------------------------------------
ServerConnection::ServerConnection(asio::io_service &inService) : m_Service(inService), m_Socket(inService)
{

}
//-----------------------------------------------------------------------------
ServerConnection::~ServerConnection()
{
    disconnect();
}
//-----------------------------------------------------------------------------
void ServerConnection::connect()
{
    if (isConnected())
        return;

    m_IsConnected = true;
    readNext();
}
//-----------------------------------------------------------------------------
void ServerConnection::disconnect()
{
    if (!isConnected())
        return;

    m_IsConnected = false;

    m_Socket.cancel(); // Прерываем все действия Read\Write
    m_Socket.close(); // Закрываем сокет

    onDisconnect();
}
//-----------------------------------------------------------------------------
bool ServerConnection::isConnected() const
{ return m_IsConnected; }
//-----------------------------------------------------------------------------
asio::ip::tcp::socket& ServerConnection::socket()
{ return m_Socket; }
//-----------------------------------------------------------------------------
asio::ip::tcp::endpoint ServerConnection::localEndPoint() const
{ return m_Socket.local_endpoint(); }
//-----------------------------------------------------------------------------
asio::ip::tcp::endpoint ServerConnection::remoteEndPoint() const
{ return m_Socket.remote_endpoint(); }
//-----------------------------------------------------------------------------
void ServerConnection::read()
{
    if (!isConnected())
        return;

    // Читать до \n
    asio::async_read_until(m_Socket, asio::dynamic_buffer(m_readBuffer), '\n', std::bind(&ServerConnection::onRead, this, _1, _2));
}
//-----------------------------------------------------------------------------
void ServerConnection::write()
{
    if (!isConnected())
        return;

    asio::async_write(m_Socket, asio::buffer(m_writeBuffer + '\n'), asio::transfer_all(), std::bind(&ServerConnection::onWrite, this, _1, _2));
}
//-----------------------------------------------------------------------------
void ServerConnection::readNext()
{
    read();
}
//-----------------------------------------------------------------------------
void ServerConnection::writeNext()
{
    write();
}
//-----------------------------------------------------------------------------
void ServerConnection::readData(const uint64_t inSize)
{
    if (!inSize)
        return;

    std::string Data = m_readBuffer.substr(0, inSize - 1);

    std::stringstream SS(Data);
    std::uint8_t ResieveVal = 0;
    SS.read(reinterpret_cast<char*>(&ResieveVal), sizeof(ResieveVal));

    std::random_device Rd;
    std::mt19937 Generator(Rd());
    std::uniform_int_distribution<std::uint8_t> ValRange(1, 255);

    std::uint8_t ResultVal = ResieveVal % ValRange(Generator);

    Data.clear();
    SS = std::stringstream(Data);
    SS.write(reinterpret_cast<char*>(&ResultVal), sizeof(ResultVal));

    m_writeBuffer = SS.str();
    write();
}
//-----------------------------------------------------------------------------
void ServerConnection::onRead(const std::error_code & inError, const uint64_t inBytes)
{
    if (inError)
    {
        switch (inError.value())
        {
            case asio::error::eof:
            {
                // no problem
                break;
            }
            case 0x86:
            case 0x7D:
            {
                std::cerr << inError.message() << std::endl;
                disconnect();
                return;
            }

            default:
            {
                std::cerr << inError.message() << " code = " << inError.value() << std::endl;
                disconnect();
                return;
            }
        }
    }

    if (!isConnected())
        return;

    readData(inBytes);
    m_readBuffer = m_readBuffer.substr(inBytes);

    readNext();
}
//-----------------------------------------------------------------------------
void ServerConnection::onWrite(const std::error_code & inError, const uint64_t inBytes)
{
    if (inError)
    {
        std::cerr << inError.message() << " code = " << inError.value() << std::endl;
        disconnect();
        return;
    }

    m_writeBuffer.clear();
}
//-----------------------------------------------------------------------------
void ServerConnection::onDisconnect()
{
    // Метод для потомка
    notify(cEventDisconnect);
}
//-----------------------------------------------------------------------------
