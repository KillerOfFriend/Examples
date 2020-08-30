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

    quint64 PackageSize;
    ePackageType Type;
    quint64 DataSize;

    Stream >> PackageSize;
    Stream >> Type;
    Stream >> DataSize;

    std::vector<CustomData> InitVals;

    while (DataSize--)
    {
        CustomData Data;
        Stream >> Data;
        InitVals.push_back(Data);
    }

    mDataStorege->init(InitVals);
}
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
void TcpClient::write(QByteArray inData)
{
    if (!mClientSocket.isOpen())
        return;

    quint64 Size = sizeof(Size) + inData.size();

    // Формируем пакет (Размер пакета[8])(Данные[~])
    QByteArray Package;
    QDataStream Stream(&Package, QIODevice::WriteOnly);
    Stream << Size;

    Package += inData;
    inData.clear();

    do
    {   // Обрабатываем возможность не полной отправки
        quint64 Sended = mClientSocket.write(Package);
        Package.remove(0, Sended);
        Size -= Sended;

    }
    while(Size);

}
//-----------------------------------------------------------------------------
void TcpClient::slot_onReadData()
{
    if (mClientSocket.bytesAvailable())
    {
        mAccumulator += mClientSocket.readAll(); // Получаем данные

        if (mReadNewPackage) // Если начинаем чтение нового пакета
        {
            mReadNewPackage = false;
            QDataStream Stream(&mAccumulator, QIODevice::ReadOnly);
            Stream >> mPackageSize; // Получаем полный размер пакета
        }

        if (mAccumulator.size() >= mPackageSize) // Если покет получен целиком
        {
            read(mAccumulator.left(mPackageSize)); // Отправляем данные на обработку

            mAccumulator.remove(0, mPackageSize); // Удаляем пакет из контейнера
            mPackageSize = 0; // Сбрасываем размер пакета
            mReadNewPackage = true; // Ожидаем нового пакета
        }
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
