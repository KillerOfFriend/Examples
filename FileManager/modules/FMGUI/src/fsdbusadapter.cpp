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
    auto result = m_qdbusInterface.copyObject(inPath);

    if (!result.isValid() || !result.value())
        QMessageBox::warning(nullptr, tr("Error"), result.error().message());
}
//-----------------------------------------------------------------------------
void FsDBusAdapter::cut(const QString &inPath)
{
    auto result = m_qdbusInterface.cutObject(inPath);

    if (!result.isValid() || !result.value())
        QMessageBox::warning(nullptr, tr("Error"), result.error().message());
}
//-----------------------------------------------------------------------------
void FsDBusAdapter::paste(const QString &inPath)
{
    auto result = m_qdbusInterface.pasteObject(inPath);

    if (!result.isValid() || !result.value())
        QMessageBox::warning(nullptr, tr("Error"), result.error().message());
}
//-----------------------------------------------------------------------------
void FsDBusAdapter::remove(const QString &inPath)
{
    auto result = m_qdbusInterface.deleteObject(inPath);

    if (!result.isValid() || !result.value())
        QMessageBox::warning(nullptr, tr("Error"), result.error().message());
}
//-----------------------------------------------------------------------------
