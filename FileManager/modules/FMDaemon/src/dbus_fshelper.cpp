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
    actionDone();
    return m_buffAction->objectIsValid();
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::cutObject(const QString& inPath)
{
    m_buffAction = std::make_unique<MoveFsAction>(inPath);
    actionDone();
    return m_buffAction->objectIsValid();
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::pasteObject(const QString& inPath)
{
    bool Result = true;

    if ( Result = !bufferIsEmpty() )
    {
        Result = m_buffAction->execute(inPath);
        // Копирование можно провести повторно, перемещение нельзя
        if (m_buffAction->m_actionType == fs::efsAcrionType::atMove)
            m_buffAction = nullptr;

        actionDone();
    }

    return Result;
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::deleteObject(const QString& inPath)
{
    bool Result = true;
    RemoveFsAction RemoveAction(inPath);

    if (Result = RemoveAction.objectIsValid())
        Result = RemoveAction.execute();

    actionDone();
    return Result;
}
//-----------------------------------------------------------------------------
bool DBusFsHelper::bufferIsEmpty() const
{
    return m_buffAction == nullptr;
}
//-----------------------------------------------------------------------------
