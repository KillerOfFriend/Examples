#ifndef FSDBUSADAPTER_H
#define FSDBUSADAPTER_H

#include "dbusfsinterface.h"

//-----------------------------------------------------------------------------
///
/// \brief The FsDBusAdapter class - Класс, описывающий адаптер интерфейса DBus
///
class FsDBusAdapter : public QObject
{
    Q_OBJECT
public:

    ///
    /// \brief FsDBusAdapter - Конструктор по умолчанию
    /// \param inParent - Указатель на объект-предок
    ///
    FsDBusAdapter(QObject *inParent = nullptr);

    ///
    /// \brief ~FsDBusAdapter - Виртуальный деструктор по умолчанию
    ///
    virtual ~FsDBusAdapter() override = default;

    ///
    /// \brief copy - Метод копирования объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    Q_INVOKABLE bool copy(const QString &inPath);

    ///
    /// \brief cut - Метод перемещения объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    Q_INVOKABLE bool cut(const QString &inPath);

    ///
    /// \brief paste - Метод вставки объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    Q_INVOKABLE bool paste(const QString &inPath);

    ///
    /// \brief remove - Метод удаления объекта
    /// \param inPath - Путь к объекту
    /// \return Вернёт признак успешности операции
    ///
    Q_INVOKABLE bool remove(const QString &inPath);

    ///
    /// \brief bufferIsEmpty -  Метод вернёт признак того, что буфер пуст
    /// \return Вернёт признак того, что буфер пуст
    ///
    Q_INVOKABLE bool bufferIsEmpty();

private:
    OrgFooDbusfilemanagerInterface m_qdbusInterface; ///< Инерфейс DBus
};
//-----------------------------------------------------------------------------

#endif // FSDBUSADAPTER_H
