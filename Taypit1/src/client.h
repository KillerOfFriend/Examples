#ifndef CLIENT_H
#define CLIENT_H

#include <system_error>

#include <asio.hpp>

//-----------------------------------------------------------------------------
enum class eStatus
{
    A,
    B,
    C,
    D,
    E,
    F
};
//-----------------------------------------------------------------------------
class Client
{
public:

    Client();
    ~Client();

    bool connect();
    void disconnect();
    bool isConnected() const;

    void process();
    eStatus status() const;

private:

    eStatus m_Status = eStatus::A;

    asio::io_service m_Service;
    asio::ip::tcp::socket m_Soket;

    std::string read();
    void write(const std::string& inData);

    eStatus changeStatus(const std::uint8_t inVal) const;
};
//-----------------------------------------------------------------------------

#endif // CLIENT_H
