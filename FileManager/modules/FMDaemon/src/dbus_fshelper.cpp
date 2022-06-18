#include "dbus_fshelper.h"

#include <QDir>

using namespace fs;

//-----------------------------------------------------------------------------
DBusFsHelper::DBusFsHelper(QObject *inParent) : QObject(inParent)
{

}
//-----------------------------------------------------------------------------
bool DBusFsHelper::copyObject(const QString& inPath)
{
    m_buffAction = std::make_unique<CopyFsAction>(inPath);
    return m_buffAction->objectIsValid();
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::cutObject(const QString& inPath)
{
    m_buffAction = std::make_unique<MoveFsAction>(inPath);
    return m_buffAction->objectIsValid();
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::pasteObject(const QString& inPath)
{
    bool Result = true;

    if ( Result = (m_buffAction != nullptr) )
        Result = m_buffAction->execute(inPath);

    m_buffAction = nullptr;
    return Result;
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::deleteObject(const QString& inPath)
{
    bool Result = true;

    m_buffAction = std::make_unique<RemoveFsAction>(inPath);

    if (Result = m_buffAction->objectIsValid())
        Result = m_buffAction->execute();

    m_buffAction = nullptr;
    return Result;
}
//-----------------------------------------------------------------------------
