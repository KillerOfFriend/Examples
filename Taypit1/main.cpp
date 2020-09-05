#include <iostream>

#include <array>
#include <thread>
#include <memory>
#include <iostream>
#include <algorithm>


#include "server.h"
#include "client.h"

//-----------------------------------------------------------------------------
struct ClientData
{
    std::size_t m_ID = 0;
    std::shared_ptr<Client> m_Client = nullptr;

    std::thread m_WorkThread;
};
//-----------------------------------------------------------------------------
bool finish(const std::array<ClientData, 32>& inClients)
{
    bool Result = true;

    for (const ClientData& C : inClients)
        Result &= !C.m_Client->isConnected();

    return Result;
}
//-----------------------------------------------------------------------------
std::string status(const ClientData& inData)
{
    std::stringstream SS;

    if (inData.m_Client)
    {
        SS << "[" << inData.m_ID << "]: ";

        switch (inData.m_Client->status())
        {
            case eStatus::A:    { SS << 'A'; break; }
            case eStatus::B:    { SS << 'B'; break; }
            case eStatus::C:    { SS << 'C'; break; }
            case eStatus::D:    { SS << 'D'; break; }
            case eStatus::E:    { SS << 'E'; break; }
            case eStatus::F:    { SS << 'F'; break; }
            default:            { SS << '?'; break; }
        }

        SS << "\t\t";
    }

    return SS.str();
}
//-----------------------------------------------------------------------------
int main()
{
    std::shared_ptr<Server> ServerTCP = std::make_shared<Server>();
    std::array<ClientData, 32> Clients;

    if (!ServerTCP->start())
        std::cerr << "Server start fail." << std::endl;
    else
    {
        bool AllConnected = true;
        // Подключаем все клиенты
        std::size_t ID = 0;
        for (auto& C : Clients)
        {
            C.m_ID = ++ID;
            C.m_Client = std::make_shared<Client>();
            AllConnected &= C.m_Client->connect();
        }
        // Запускаем обработку
        if (AllConnected)
            for (auto& C : Clients)
                C.m_WorkThread = std::thread(&Client::process, C.m_Client.get());

        // Ожидание и визуализация:
        while(!finish(Clients))
        {
            system("clear");

            std::size_t Index = 0;

            for (std::size_t I = 0; I < 8; ++I)
            {
                std::cout << status(Clients[Index]) << status(Clients[Index + 1]) << status(Clients[Index + 2]) << status(Clients[Index + 3]) << std::endl;
                Index += 4;
            };

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        // Разрываем все соединения
        for (auto& C : Clients)
            if (C.m_Client)
            {
                C.m_Client->disconnect();
                if (C.m_WorkThread.joinable())
                    C.m_WorkThread.join();
            }

        std::cout << "Work Finish." << std::endl;
    }

    return 0;
}
//-----------------------------------------------------------------------------
