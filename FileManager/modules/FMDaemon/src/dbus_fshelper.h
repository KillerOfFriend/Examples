#ifndef DBUS_FSHELPER_H
#define DBUS_FSHELPER_H

#include <memory>

#include <QObject>
#include <QtDBus/QtDBus>

#include "dbus_defines.hpp"
#include "fsaction.h"

namespace fs
{
//-----------------------------------------------------------------------------
///
/// \brief The DBusFsHelper class - Класс, описывающий интерфейс управления объектами файловой системой
///
class DBusFsHelper : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DBUS_SERVICE_NAME)
public:

    ///
    /// \brief DBusFsHelper - Конструктор по умолчанию
    /// \param inParent - Указатель на объект-предок
    ///
    explicit DBusFsHelper(QObject *inParent = nullptr);

    ///
    /// \brief ~DBusFsHelper - Виртуальный деструктор по умолчанию
    ///
    virtual ~DBusFsHelper() override = default;

public slots:

    ///
    /// \brief copyObject - Слот копирования объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    bool copyObject(const QString& inPath);

    ///
    /// \brief cutObject - Слот перемещения объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    bool cutObject(const QString& inPath);

    ///
    /// \brief pasteObject - Слот вставки объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    bool pasteObject(const QString& inPath);

    ///
    /// \brief deleteObject - Слот удаления объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    bool deleteObject(const QString& inPath);

    ///
    /// \brief bufferIsEmpty - Метод вернёт признак того, что буфер пуст
    /// \return Вернёт признак того, что буфер пуст
    ///
    bool bufferIsEmpty() const;

private:

    std::unique_ptr<AbstractFsAction> m_buffAction; ///< Буфер с подготовленным действием копирования или удаления

};
//-----------------------------------------------------------------------------
} // namespace fs

#endif // DBUS_FSHELPER_H
