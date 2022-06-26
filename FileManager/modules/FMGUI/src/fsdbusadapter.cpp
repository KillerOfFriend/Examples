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
    auto response = m_qdbusInterface.bufferIsEmpty(); // Вызываем метод по DBus
    response.waitForFinished(); // Ожидаем завершения выполнения метода

    return (response.isValid()) ? response.value() : false;
}
//-----------------------------------------------------------------------------

