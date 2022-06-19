#include "fsdbusadapter.h"

#include <QMessageBox>
#include <QDBusConnection>

#include "dbus_defines.hpp"

//-----------------------------------------------------------------------------
FsDBusAdapter::FsDBusAdapter(QObject *inParent) :
    QObject(inParent),
    m_qdbusInterface{ DBUS_SERVICE_NAME, DBUS_OBJECT_NAME, QDBusConnection::sessionBus(), this }
{

}
//-----------------------------------------------------------------------------
bool FsDBusAdapter::copy(const QString &inPath)
{
    checkCallHelper();
    auto response = m_qdbusInterface.copyObject(inPath); // Вызываем метод по DBus
    response.waitForFinished(); // Ожидаем завершения выполнения метода

    bool Result = response.isValid() && response.value();

    if (!Result) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), response.error().message()); // Выводим соответствующее сообщение

    return Result;
}
//-----------------------------------------------------------------------------
bool FsDBusAdapter::cut(const QString &inPath)
{
    checkCallHelper();
    auto response = m_qdbusInterface.cutObject(inPath); // Вызываем метод по DBus
    response.waitForFinished(); // Ожидаем завершения выполнения метода

    bool Result = response.isValid() && response.value();

    if (!Result) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), response.error().message()); // Выводим соответствующее сообщение

    return Result;
}
//-----------------------------------------------------------------------------
bool FsDBusAdapter::paste(const QString &inPath)
{
    checkCallHelper();
    auto response = m_qdbusInterface.pasteObject(inPath); // Вызываем метод по DBus
    response.waitForFinished(); // Ожидаем завершения выполнения метода

    bool Result = response.isValid() && response.value();

    if (!Result) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), response.error().message()); // Выводим соответствующее сообщение

    return Result;
}
//-----------------------------------------------------------------------------
bool FsDBusAdapter::remove(const QString &inPath)
{
    checkCallHelper();
    auto response = m_qdbusInterface.deleteObject(inPath); // Вызываем метод по DBus
    response.waitForFinished(); // Ожидаем завершения выполнения метода

    bool Result = response.isValid() && response.value();

    if (!Result) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), response.error().message()); // Выводим соответствующее сообщение

    return Result;
}
//-----------------------------------------------------------------------------
bool FsDBusAdapter::bufferIsEmpty()
{
    checkCallHelper();
    auto response = m_qdbusInterface.bufferIsEmpty(); // Вызываем метод по DBus
    response.waitForFinished(); // Ожидаем завершения выполнения метода

    return (response.isValid()) ? response.value() : false;
}
//-----------------------------------------------------------------------------
bool FsDBusAdapter::checkCallHelper()
{
    bool Result = true;

    if (Result = QDBusConnection::sessionBus().isConnected())
    {
        QDBusConnectionInterface* DBusInterface = QDBusConnection::sessionBus().interface();

        // Ищим приложение хелпер
        if(!DBusInterface->registeredServiceNames().value().contains(DBUS_SERVICE_NAME))
        {   // Хелпер не зарегестрирован

            auto response = std::system("nohup " DBUS_SERVICE_INSTALL_PATH "//FMDaemon > /dev/null &"); // Запускаем
            Q_UNUSED(response)
            Result = DBusInterface->registeredServiceNames().value().contains(DBUS_SERVICE_NAME); // Проверяем что сервис запустился
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
