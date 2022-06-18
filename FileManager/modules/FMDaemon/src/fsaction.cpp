#include "fsaction.h"

#include <QDir>

namespace fs
{
//-----------------------------------------------------------------------------
bool copyDirectory(const QDir& inFrom, const QDir& inTo, const bool inRecursive = true)
{
    bool Result = true;

    if (!inTo.exists())
        inTo.mkpath(inTo.path());

    if ( Result = (inFrom.exists() &&
                   QFileInfo(inFrom.path()).isDir() &&
                   QFileInfo(inTo.path()).isDir()))
    {
        for (const auto& objectPath : inFrom.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
        {
            if (objectPath.isDir())
                Result = (inRecursive) ? copyDirectory(objectPath.absoluteFilePath(), inTo.filePath(objectPath.baseName())) : true;
            else
            {
                QString Dest = inTo.filePath(objectPath.fileName());

                if (QFile::exists(Dest))
                    QFile::remove(Dest);

                Result = QFile::copy(objectPath.absoluteFilePath(), Dest);
            }

            if (!Result)
                break;
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
} // namespace fs

using namespace fs;

//-----------------------------------------------------------------------------
// AbstractFsAction
//-----------------------------------------------------------------------------
AbstractFsAction::AbstractFsAction() :
    m_actionType(efsAcrionType::atUnknown),
    m_objectPath("")
{

}
//-----------------------------------------------------------------------------
AbstractFsAction::AbstractFsAction(const QString &inPath) :
    m_actionType(efsAcrionType::atUnknown),
    m_objectPath(inPath)
{

}
//-----------------------------------------------------------------------------
bool AbstractFsAction::objectIsValid() const
{
    return QDir().exists(m_objectPath);
}
//-----------------------------------------------------------------------------
// CopyFsAction
//-----------------------------------------------------------------------------
CopyFsAction::CopyFsAction() : AbstractFsAction()
{
    m_actionType = efsAcrionType::atCopy;
}
//-----------------------------------------------------------------------------
CopyFsAction::CopyFsAction(const QString &inPath) : AbstractFsAction(inPath)
{
    m_actionType = efsAcrionType::atCopy;
}
//-----------------------------------------------------------------------------
bool CopyFsAction::execute(const QString& inPath) const
{
    bool Result = true;

    if ( Result = (objectIsValid() && QDir().exists(inPath)) )
        Result = (QFileInfo(m_objectPath).isDir()) ? copyDirectory(m_objectPath, inPath) : QFile::copy(m_objectPath, inPath);

    return Result;
}
//-----------------------------------------------------------------------------
// MoveFsAction
//-----------------------------------------------------------------------------
MoveFsAction::MoveFsAction() : AbstractFsAction()
{
    m_actionType = efsAcrionType::atMove;
}
//-----------------------------------------------------------------------------
MoveFsAction::MoveFsAction(const QString &inPath) : AbstractFsAction(inPath)
{
    m_actionType = efsAcrionType::atMove;
}
//-----------------------------------------------------------------------------
bool MoveFsAction::execute(const QString& inPath) const
{
    bool Result = true;

    if ( Result = (objectIsValid() && !QDir().exists(inPath)) )
        Result = QDir().rename(m_objectPath, inPath);

    return Result;
}
//-----------------------------------------------------------------------------
// RemoveFsAction
//-----------------------------------------------------------------------------
RemoveFsAction::RemoveFsAction() : AbstractFsAction()
{
    m_actionType = efsAcrionType::atRemove;
}
//-----------------------------------------------------------------------------
RemoveFsAction::RemoveFsAction(const QString &inPath) : AbstractFsAction(inPath)
{
    m_actionType = efsAcrionType::atRemove;
}
//-----------------------------------------------------------------------------
bool RemoveFsAction::execute(const QString& inPath) const
{
    Q_UNUSED(inPath)
    bool Result = true;

    if (Result = objectIsValid())
        Result = (QFileInfo(m_objectPath).isDir()) ? QDir(m_objectPath).removeRecursively() : QDir().remove(m_objectPath);

    return Result;
}
//-----------------------------------------------------------------------------
