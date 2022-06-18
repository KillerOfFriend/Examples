#ifndef FSACTION_H
#define FSACTION_H

#include <QString>

namespace fs
{
//-----------------------------------------------------------------------------
///
/// \brief The efsAcrionType enum - Перечеслиение действий над объектами файловой системы
///
enum class efsAcrionType
{
    atUnknown =     0,  ///< Тип действия не орпределён
    atCopy =        1,  ///< Копирование объекта
    atMove =        2,  ///< Перемещение объекта
    atRemove =      3   ///< Удаление объекта
};
//-----------------------------------------------------------------------------
///
/// \brief The AbstractFsAction class - Класс, описывающий абстрактное действие над объектом файловой системы
///
class AbstractFsAction
{
public:

    AbstractFsAction();
    AbstractFsAction(const QString& inPath);

    virtual ~AbstractFsAction() = default;

    bool objectIsValid() const;
    virtual bool execute(const QString& inPath = {}) const = 0;

protected:

    efsAcrionType m_actionType; ///< Тип действия
    QString m_objectPath;       ///< Путь к объекту
};
//-----------------------------------------------------------------------------
class CopyFsAction : public AbstractFsAction
{
public:

    CopyFsAction();
    CopyFsAction(const QString& inPath);

    virtual ~CopyFsAction() override = default;

    virtual bool execute(const QString& inPath = {}) const override;

};
//-----------------------------------------------------------------------------
class MoveFsAction : public AbstractFsAction
{
public:

    MoveFsAction();
    MoveFsAction(const QString& inPath);

    virtual ~MoveFsAction() override = default;

    virtual bool execute(const QString& inPath = {}) const override;

};
//-----------------------------------------------------------------------------
class RemoveFsAction : public AbstractFsAction
{
public:

    RemoveFsAction();
    RemoveFsAction(const QString& inPath);

    virtual ~RemoveFsAction() override = default;

    virtual bool execute(const QString& inPath = {}) const override;

};
//-----------------------------------------------------------------------------
} // namespace fs

#endif // FSACTION_H
