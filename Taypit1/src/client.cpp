#include "client.h"

#include <iostream>
#include <sstream>
#include <random>
#include <chrono>

//-----------------------------------------------------------------------------
Client::Client() : m_Soket(m_Service)
{

}
//-----------------------------------------------------------------------------
Client::~Client()
{
    disconnect();
    m_Service.stop();
}
//-----------------------------------------------------------------------------
bool Client::connect()
{
    disconnect();

    std::error_code Err;
    m_Soket.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 8564), Err);

    if (Err)
    {
        std::cerr << Err.message() << std::endl;
        return false;
    }
    else
        return true;
}
//-----------------------------------------------------------------------------
void Client::disconnect()
{
    if (m_Soket.is_open())
        m_Soket.close();
}
//-----------------------------------------------------------------------------
bool Client::isConnected() const
{ return m_Soket.is_open(); }
//-----------------------------------------------------------------------------
void Client::process()
{
    if (!isConnected())
        return;

    std::random_device Rd;
    std::mt19937 Generator(Rd());

    std::uniform_int_distribution<std::uint8_t> ValRange(1, 255);
    std::uniform_int_distribution<std::uint8_t> SleepRange(1, 3);

    while (m_Status != eStatus::F)
    {
        std::stringstream SS;
        std::uint8_t Val = ValRange(Generator);
        SS.write(reinterpret_cast<char*>(&Val), sizeof(Val));

        write(SS.str());
        std::string Data = read();
        SS = std::stringstream(Data);
        SS.read(reinterpret_cast<char*>(&Val), sizeof(Val));

        m_Status = changeStatus(Val);
        std::this_thread::sleep_for(std::chrono::seconds(SleepRange(Generator)));
    }

    disconnect();
}
//----------------------------------------------------------------------------
eStatus Client::status() const
{ return m_Status; }
//----------------------------------------------------------------------------
std::string Client::read()
{
    if (!isConnected())
        return {};

    asio::streambuf StreamBuf;
    asio::read_until(m_Soket, StreamBuf, '\n');

    return std::string(asio::buffer_cast<const char*>(StreamBuf.data()));
}
//-----------------------------------------------------------------------------
void Client::write(const std::string& inData)
{
    if (!isConnected())
        return;

    asio::write(m_Soket, asio::buffer(inData + '\n'), asio::transfer_all());
}
//-----------------------------------------------------------------------------
eStatus Client::changeStatus(const uint8_t inVal) const
{
    eStatus Result;

    switch (m_Status)
    {
        case eStatus::A:
        {
            Result = (inVal >= 10) ? eStatus::B : ((inVal < 5) ? eStatus::C : eStatus::A);
            break;
        };

        case eStatus::B:
        {
            Result = (inVal >= 50) ? eStatus::C : ((inVal < 5) ? eStatus::D : eStatus::B);
            break;
        };

        case eStatus::C:
        {
            Result = (inVal >= 90) ? eStatus::D : ((inVal < 5) ? eStatus::E : eStatus::C);
            break;
        };

        case eStatus::D:
        {
            Result = (inVal >= 130) ? eStatus::D : ((inVal < 5) ? eStatus::F : eStatus::E);
            break;
        };

        case eStatus::E:
        {
            Result = (inVal >= 170) ? eStatus::F : ((inVal < 5) ? eStatus::A : eStatus::E);
            break;
        };

        case eStatus::F:
        {
            Result = eStatus::F;
            break;
        };

        default: { Result = m_Status; break; }
    }

    return Result;
}
//-----------------------------------------------------------------------------
