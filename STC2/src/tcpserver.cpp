#include "tcpserver.h"

#include <QDataStream>

#include <tools.h>

//-----------------------------------------------------------------------------
TcpServer::TcpServer(const QHostAddress inHostAddres, const quint16 inPort,
                     const std::shared_ptr<DataStorege> inDataStorege, QObject* inParent)
    : NetWork(inDataStorege, inParent),
      mHostAddres(inHostAddres),
      mPort(inPort)
{
    connect(&mServer, &QTcpServer::newConnection, this, &TcpServer::slot_onNewConnection);
}
//-----------------------------------------------------------------------------
TcpServer::~TcpServer()
{
    stop();
}
//-----------------------------------------------------------------------------
bool TcpServer::start()
{
    stop();

    mServer.setMaxPendingConnections(1); // Только одно соединение
    return mServer.listen(mHostAddres, mPort);
}
//-----------------------------------------------------------------------------
void TcpServer::stop()
{
    mServer.close();
}
//-----------------------------------------------------------------------------
void TcpServer::onInit(QByteArray inInitData)
{ // Обрабатываем запрос на инициализацию от клиента
    Q_UNUSED(inInitData);

    QByteArray Data;
    QDataStream Stream(&Data, QIODevice::WriteOnly);

    std::vector<CustomData> Dump = mDataStorege->dump();

    Stream << ePackageType::ptInit << static_cast<quint64>(Dump.size());

    for (CustomData& CC : Dump)
        Stream << CC;

    write(Data);
}
//-----------------------------------------------------------------------------
void TcpServer::write(QByteArray inData)
{
    if (!mServer.isListening())
        return;

    std::lock_guard<std::mutex> lg(mConnectionsDefender);
    for (const std::pair<QTcpSocket*, std::shared_ptr<ConnectionData>>& Connection : mConnections)
    {
        quint64 Size = sizeof(Size) + inData.size();

        // Формируем пакет (Размер пакета[8])(Данные[~])
        QByteArray Package;
        QDataStream Stream(&Package, QIODevice::WriteOnly);
        Stream << Size;

        Package += inData;

        do
        {   // Обрабатываем возможность не полной отправки
            quint64 Sended = Connection.first->write(Package);
            Package.remove(0, Sended);
            Size -= Sended;

        }
        while(Size);

    }

    inData.clear();
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void TcpServer::slot_onNewConnection()
{
    QTcpSocket* NewConnection = mServer.nextPendingConnection();

    if (mConnections.size() >= mServer.maxPendingConnections())
    {
        NewConnection->disconnect();
        NewConnection->close();
        NewConnection->deleteLater();
    }
    else
    {
        std::lock_guard<std::mutex> lg(mConnectionsDefender);
        mConnections.insert(std::make_pair(NewConnection, std::make_shared<ConnectionData>()));

        connect(NewConnection, &QTcpSocket::readyRead, this, &TcpServer::slot_onClientReadData); // Готовность к чтению данных
        connect(NewConnection, &QTcpSocket::disconnected, this, &TcpServer::slot_onClientDisconnect); // Отключение клиента
        connect(NewConnection, QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error), this, &TcpServer::slot_onError); // Ошибка сокета клиента
    }
}
//-----------------------------------------------------------------------------
void TcpServer::slot_onClientDisconnect()
{
    QTcpSocket* Connection = qobject_cast<QTcpSocket*>(QObject::sender());

    if (Connection)
    {
        std::lock_guard<std::mutex> lg(mConnectionsDefender);
        mConnections.erase(Connection);
    }
}
//-----------------------------------------------------------------------------
void TcpServer::slot_onClientReadData()
{
    QTcpSocket* Connection = qobject_cast<QTcpSocket*>(QObject::sender());

    if (Connection && Connection->bytesAvailable())
    {
        std::shared_ptr<ConnectionData> ConData = nullptr;

        {
            std::lock_guard<std::mutex> lg(mConnectionsDefender);

            auto FindRes = mConnections.find(Connection);

            if (FindRes != mConnections.end())
                ConData = FindRes->second;
        }

        if (!ConData)
            return;

        ConData->mAccumulator += Connection->readAll(); // Получаем данные

        if (ConData->mReadNewPackage) // Если начинаем чтение нового пакета
        {
            ConData->mReadNewPackage = false;
            QDataStream Stream(&ConData->mAccumulator, QIODevice::ReadOnly);
            Stream >> ConData->mPackageSize; // Получаем полный размер пакета
        }

        if (ConData->mAccumulator.size() >= ConData->mPackageSize) // Если покет получен целиком
        {
            read(ConData->mAccumulator.left(ConData->mPackageSize)); // Отправляем данные на обработку

            ConData->mAccumulator.remove(0, ConData->mPackageSize); // Удаляем пакет из контейнера
            ConData->mPackageSize = 0; // Сбрасываем размер пакета
            ConData->mReadNewPackage = true; // Ожидаем нового пакета
        }
    }
}
//-----------------------------------------------------------------------------
void TcpServer::slot_onError(QAbstractSocket::SocketError inErr)
{
    qDebug() << "Socket Error: " << inErr;
}
//-----------------------------------------------------------------------------
