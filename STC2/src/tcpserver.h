#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <set>
#include <mutex>

#include "network.h"

#include <QTcpServer>
#include <QTcpSocket>

//-----------------------------------------------------------------------------
class TcpServer : public NetWork
{
public:    

    /**
     * @brief TcpServer - Инициализирующий конструктор
     * @param inHostAddres - Адресный диапазон хоста
     * @param inPort - Порт хоста
     * @param inDataStorege - Указатель на хранилище данных
     * @param inParent - Объект-предок
     */
    TcpServer(const QHostAddress inHostAddres, const quint16 inPort,
            const std::shared_ptr<DataStorege> inDataStorege, QObject* inParent = nullptr);

    /**
     * @brief ~TcpServer - Виртуальный деструктор
     */
    virtual ~TcpServer() override;

    /**
     * @brief start - Метод запусти соединение
     * @return Вернёт признак успешности операции
     */
    virtual bool start() override;

    /**
     * @brief stop - Метод остановит соединение
     */
    virtual void stop() override;

    /**
     * @brief onInit - Метод обработает запрос инициализации
     * @param inInitData - Данные инициализации
     */
    virtual void onInit(QByteArray inInitData) override;

private:

    const QHostAddress mHostAddres; ///< Адресный диапазон хоста
    const quint16 mPort; ///< Порт хоста

    QTcpServer mServer; ///< Сервер
    std::set<QTcpSocket*> mConnections; ///< Перечень соеденений
    std::mutex mConnectionsDefender; ///< Мьютекс, защищающий соединения

    /**
     * @brief write - Метод отправит данные по сокету
     * @param inData - Отправляемые данные
     */
    virtual void write(const QByteArray inData) override;

private slots:

    /**
     * @brief slot_onNewConnection - Слот, реагирующий на подключение нового клиента
     */
    void slot_onNewConnection();

    /**
     * @brief slot_onClientDisconnect - Слот, реагирующий на отключение клиента
     */
    void slot_onClientDisconnect();

    /**
     * @brief slot_onClientReadData - Слот, реагирующий на готовность к чтению данных от клиентов
     */
    void slot_onClientReadData();

    /**
     * @brief slot_onError - Слот, реагирующий на ошибку сокета
     * @param inErr - Ошибка
     */
    void slot_onError(QAbstractSocket::SocketError inErr);


};
//-----------------------------------------------------------------------------

#endif // TCPSERVER_H
