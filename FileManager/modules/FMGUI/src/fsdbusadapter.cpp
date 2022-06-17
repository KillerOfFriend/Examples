#include "fsdbusadapter.h"

#include <QMessageBox>

#include "dbus_defines.hpp"

//-----------------------------------------------------------------------------
FsDBusAdapter::FsDBusAdapter(QObject *inParent) :
    QObject(inParent),
    m_qdbusInterface{ DBUS_SERVICE_NAME, DBUS_OBJECT_NAME, QDBusConnection::sessionBus(), this }
{

}
//-----------------------------------------------------------------------------
void FsDBusAdapter::copy(const QString &inPath)
{
    auto result = m_qdbusInterface.copyObject(inPath); // Вызываем метод по DBus
    result.waitForFinished(); // Ожидаем завершения выполнения метода

    if (!result.isValid() || !result.value()) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), result.error().message()); // Выводим соответствующее сообщение
}
//-----------------------------------------------------------------------------
void FsDBusAdapter::cut(const QString &inPath)
{
    auto result = m_qdbusInterface.cutObject(inPath); // Вызываем метод по DBus
    result.waitForFinished(); // Ожидаем завершения выполнения метода

    if (!result.isValid() || !result.value()) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), result.error().message()); // Выводим соответствующее сообщение);
}
//-----------------------------------------------------------------------------
void FsDBusAdapter::paste(const QString &inPath)
{
    auto result = m_qdbusInterface.pasteObject(inPath); // Вызываем метод по DBus
    result.waitForFinished(); // Ожидаем завершения выполнения метода

    if (!result.isValid() || !result.value()) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), result.error().message()); // Выводим соответствующее сообщение
}
//-----------------------------------------------------------------------------
void FsDBusAdapter::remove(const QString &inPath)
{
    auto result = m_qdbusInterface.deleteObject(inPath); // Вызываем метод по DBus
    result.waitForFinished(); // Ожидаем завершения выполнения метода

    if (!result.isValid() || !result.value()) // В случаи ошибки
        QMessageBox::warning(nullptr, tr("Error"), result.error().message()); // Выводим соответствующее сообщение
}
//-----------------------------------------------------------------------------
