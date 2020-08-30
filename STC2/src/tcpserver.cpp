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
    connect(&mServer, &QTcpServer::newConnection, this, &TcpServer::slot_NewConnection);
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
void TcpServer::write(const QByteArray inData)
{
    if (!mServer.isListening())
        return;

    std::lock_guard<std::mutex> lg(mConnectionsDefender);
    for (QTcpSocket* Connection : mConnections)
        Connection->write(inData);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void TcpServer::slot_NewConnection()
{
    QTcpSocket* NewConnection = mServer.nextPendingConnection();

    {
        std::lock_guard<std::mutex> lg(mConnectionsDefender);
        mConnections.insert(NewConnection);
    }

    connect(NewConnection, &QTcpSocket::readyRead, this, &TcpServer::slot_ClientReadData); // Готовность к чтению данных
    connect(NewConnection, &QTcpSocket::disconnected, this, &TcpServer::slot_ClientDisconnect); // Отключение клиента
//    connect(NewConnection, &QAbstractSocket::stateChanged, this, &TcpServer::slot_ClientChangeState); // Изменение статуса клиента
//    connect(NewConnection, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpServer::slot_ClientError); // Ошибка сокета клиента

}
//-----------------------------------------------------------------------------
void TcpServer::slot_ClientDisconnect()
{
    QTcpSocket* Connection = qobject_cast<QTcpSocket*>(QObject::sender());

    if (Connection)
    {
        std::lock_guard<std::mutex> lg(mConnectionsDefender);
        mConnections.erase(Connection);
    }
}
//-----------------------------------------------------------------------------
void TcpServer::slot_ClientReadData()
{
    QTcpSocket* Connection = qobject_cast<QTcpSocket*>(QObject::sender());

    if (Connection && Connection->bytesAvailable())
    {
        read(Connection->readAll());
    }
}
//-----------------------------------------------------------------------------
