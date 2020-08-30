#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QHostAddress>

#include "network.h"

//-----------------------------------------------------------------------------
class TcpClient : public NetWork
{
public:

    /**
     * @brief TcpClient - Инициализирующий конструктор
     * @param inHostAddres - Адресный диапазон хоста
     * @param inPort - Порт хоста
     * @param inDataStorege - Указатель на хранилище данных
     * @param inParent - Объект-предок
     */
    TcpClient(const QHostAddress inHostAddres, const quint16 inPort,
              const std::shared_ptr<DataStorege> inDataStorege, QObject* inParent = nullptr);

    /**
     * @brief ~TcpClient - Виртуальный деструктор
     */
    virtual ~TcpClient() override;

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

    QTcpSocket mClientSocket;

    /**
     * @brief write - Метод отправит данные по сокету
     * @param inData - Отправляемые данные
     */
    virtual void write(const QByteArray inData) override;

private slots:

    void slot_onReadData();

};
//-----------------------------------------------------------------------------

#endif // TCPCLIENT_H
