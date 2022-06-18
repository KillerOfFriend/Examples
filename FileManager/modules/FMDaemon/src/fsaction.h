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

    const efsAcrionType m_actionType;   ///< Тип действия

    ///
    /// \brief AbstractFsAction - Конструктор действия
    /// \param inPath - Путь объекта ФС
    /// \param inActionType - Тип действия
    ///
    AbstractFsAction(const QString& inPath = "", const efsAcrionType inActionType = efsAcrionType::atUnknown);

    ///
    /// \brief ~AbstractFsAction - Виртуальный деструктор по умолчанию
    ///
    virtual ~AbstractFsAction() = default;


    ///
    /// \brief objectIsValid - Метод проверит валидность объекта
    /// \return Если объект валиден вернёт true в противном случаи false
    ///
    bool objectIsValid() const;

    ///
    /// \brief execute - Метод выполнит действие над объектом
    /// \return Вернёт признак успешности операции
    ///
    virtual bool execute(const QString& inPath = {}) const = 0;

protected:

    QString m_objectPath;               ///< Путь к объекту
};
//-----------------------------------------------------------------------------
///
/// \brief The CopyFsAction class - Класс описывающий действие копирования
///
class CopyFsAction : public AbstractFsAction
{
public:

    ///
    /// \brief CopyFsAction - Конструктор действия копирования
    /// \param inPath - Путь объекта ФС
    ///
    CopyFsAction(const QString& inPath);

    ///
    /// \brief ~CopyFsAction - Виртуальный деструктор по умолчанию
    ///
    virtual ~CopyFsAction() override = default;


    ///
    /// \brief execute - Метод выполнит действие над объектом
    /// \return Вернёт признак успешности операции
    ///
    virtual bool execute(const QString& inPath = {}) const override;

};
//-----------------------------------------------------------------------------
class MoveFsAction : public AbstractFsAction
{
public:

    ///
    /// \brief MoveFsAction - Конструктор действия перемещения
    /// \param inPath - Путь объекта ФС
    ///
    MoveFsAction(const QString& inPath);

    ///
    /// \brief ~MoveFsAction - Виртуальный деструктор по умолчанию
    ///
    virtual ~MoveFsAction() override = default;


    ///
    /// \brief execute - Метод выполнит действие над объектом
    /// \return Вернёт признак успешности операции
    ///
    virtual bool execute(const QString& inPath = {}) const override;

};
//-----------------------------------------------------------------------------
class RemoveFsAction : public AbstractFsAction
{
public:

    ///
    /// \brief RemoveFsAction - Конструктор действия удаления
    /// \param inPath - Путь объекта ФС
    ///
    RemoveFsAction(const QString& inPath);

    ///
    /// \brief ~RemoveFsAction - Виртуальный деструктор по умолчанию
    ///
    virtual ~RemoveFsAction() override = default;


    ///
    /// \brief execute - Метод выполнит действие над объектом
    /// \return Вернёт признак успешности операции
    ///
    virtual bool execute(const QString& inPath = {}) const override;

};
//-----------------------------------------------------------------------------
} // namespace fs

#endif // FSACTION_H
