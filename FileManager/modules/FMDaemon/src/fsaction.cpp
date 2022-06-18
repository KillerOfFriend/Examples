#include "fsaction.h"

#include <QDir>

namespace fs
{
//-----------------------------------------------------------------------------
///
/// \brief copyDirectory - Функция копирования директории
/// \param inFrom - Путь к копируемой директории
/// \param inTo - Путь назначения
/// \param inRecursive - Флаг, разрешающий рекурсивное копирование
/// \return Вернёт признак успешности операции
///
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
                QFile::remove(inTo.filePath(objectPath.fileName()));
                Result = QFile::copy(objectPath.absoluteFilePath(), inTo.filePath(objectPath.fileName()));
            }

            if (!Result)
                break;
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
///
/// \brief moveDirectory - Функция перемещения директории
/// \param inFrom - Путь к перемещаемой директории
/// \param inTo - Путь назначения
/// \return Вернёт признак успешности операции
///
bool moveDirectory(const QDir& inFrom, const QDir& inTo)
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
                Result = moveDirectory(objectPath.absoluteFilePath(), inTo.filePath(objectPath.baseName()));
            else
            {
                QFile::remove(inTo.filePath(objectPath.fileName()));
                Result = QFile::rename(objectPath.absoluteFilePath(), inTo.filePath(objectPath.fileName()));
            }

            if (!Result)
                break;
        }

        if (Result)
            QDir(inFrom).removeRecursively();
    }

    return Result;
}
//-----------------------------------------------------------------------------
} // namespace fs

using namespace fs;

//-----------------------------------------------------------------------------
// AbstractFsAction
//-----------------------------------------------------------------------------
AbstractFsAction::AbstractFsAction(const QString &inPath, const efsAcrionType inActionType) :
    m_actionType(inActionType),
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
CopyFsAction::CopyFsAction(const QString &inPath) : AbstractFsAction(inPath, efsAcrionType::atCopy)
{

}
//-----------------------------------------------------------------------------
bool CopyFsAction::execute(const QString& inPath) const
{
    bool Result = true;
    // кОпируемый объект валиден и путь копирования существует
    if ( Result = (objectIsValid() && QDir().exists(inPath)) )
    {   // Копировать объект самого в себя запрещено (для директорий)
        if ( Result = !inPath.contains(m_objectPath) )
        {
            QFileInfo ObjectInfo(m_objectPath);
            QString dest = QDir(inPath).filePath(ObjectInfo.fileName());

            // Вставка объекта в ту же директорию, откуда и копироется (До нескольких вставок подряд)
            if (m_objectPath == dest)
            {
                size_t Index = 0;
                dest = QDir(inPath).filePath(QObject::tr("copy_") + ObjectInfo.fileName());

                while (QDir().exists(dest))
                {
                    dest = QDir(inPath).filePath(QObject::tr("copy%1_").arg(Index) + ObjectInfo.fileName());
                    Index++;
                }
            }

            Result = (QFileInfo(m_objectPath).isDir()) ? copyDirectory(m_objectPath, dest) : QFile::copy(m_objectPath, dest);
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
// MoveFsAction
//-----------------------------------------------------------------------------
MoveFsAction::MoveFsAction(const QString &inPath) : AbstractFsAction(inPath, efsAcrionType::atMove)
{

}
//-----------------------------------------------------------------------------
bool MoveFsAction::execute(const QString& inPath) const
{
    bool Result = true;

    if ( Result = (objectIsValid() && QDir().exists(inPath)) )
    {   // Перемещать объект самого в себя запрещено (для директорий)
        if ( Result = !inPath.contains(m_objectPath) )
        {
            QFileInfo ObjectInfo(m_objectPath);
            QString dest = QDir(inPath).filePath(ObjectInfo.fileName());
            // Перемещение на предыдущее место игнорируется
            Result = (m_objectPath == dest) ? true : (QFileInfo(m_objectPath).isDir()) ? moveDirectory(m_objectPath, dest) : QFile::rename(m_objectPath, dest);
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
// RemoveFsAction
//-----------------------------------------------------------------------------
RemoveFsAction::RemoveFsAction(const QString &inPath) : AbstractFsAction(inPath, efsAcrionType::atRemove)
{

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
