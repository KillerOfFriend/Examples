#include "tcpclient.h"

#include <QApplication>

#include "tools.h"

//-----------------------------------------------------------------------------
TcpClient::TcpClient(const QHostAddress inHostAddres, const quint16 inPort,
                     const std::shared_ptr<DataStorege> inDataStorege, QObject* inParent)
    : NetWork(inDataStorege, inParent),
      mHostAddres(inHostAddres),
      mPort(inPort)
{
    connect(&mClientSocket, &QTcpSocket::readyRead, this, &TcpClient::slot_onReadData);
    connect(&mClientSocket, &QTcpSocket::disconnected, this, &TcpClient::slot_onDisconnect);
}
//-----------------------------------------------------------------------------
TcpClient::~TcpClient()
{
    stop();
}
//-----------------------------------------------------------------------------
bool TcpClient::start()
{
    mClientSocket.connectToHost(mHostAddres, mPort);
    bool Result = mClientSocket.isOpen();

    if (Result) // Если соединение прошло успешно
    {   // Запрашиваем инициализацию
        QByteArray Data;
        QDataStream Stream(&Data, QIODevice::WriteOnly);
        Stream << ePackageType::ptInit;

        write(Data);
    }

    return Result;
}
//-----------------------------------------------------------------------------
void TcpClient::stop()
{
    mClientSocket.close();
}
//-----------------------------------------------------------------------------
void TcpClient::onInit(QByteArray inInitData)
{
    QDataStream Stream(&inInitData, QIODevice::ReadOnly);

    ePackageType Type;
    quint64 Size;

    Stream >> Type;
    Stream >> Size;

    std::vector<CustomData> InitVals;

    while (Size--)
    {
        CustomData Data;
        Stream >> Data;
        InitVals.push_back(Data);
    }

    mDataStorege->init(InitVals);
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
void TcpClient::write(const QByteArray inData)
{
    if (!mClientSocket.isOpen())
        return;

    mClientSocket.write(inData);
}
//-----------------------------------------------------------------------------
void TcpClient::slot_onReadData()
{
    if (mClientSocket.bytesAvailable())
    {
        read(mClientSocket.readAll());
    }
}
//-----------------------------------------------------------------------------
void TcpClient::slot_onDisconnect()
{
    mClientSocket.close();
    QApplication::closeAllWindows();
}
//-----------------------------------------------------------------------------
void TcpClient::slot_onError(QAbstractSocket::SocketError inErr)
{
    qDebug() << "Socket Error: " << inErr;
}
//-----------------------------------------------------------------------------
