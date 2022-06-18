#ifndef DEATHTIMER_H
#define DEATHTIMER_H

#include <QObject>
#include <QTimer>

#include "object_restrictions.hpp"

//-----------------------------------------------------------------------------
///
/// \brief The DeathTimer class - Синглтон, описывающий таймер завершения работы приложения
///
class DeathTimer : public QObject, ors::FixedObject
{
    Q_OBJECT
public:

    ///
    /// \brief Instance - Метод вернёт ссылку на единственный экземпляр объетка
    /// \return Вернёт ссылку на объект
    ///
    static DeathTimer& Instance();

private:

    QTimer m_timer; ///< Таймер

    ///
    /// \brief DeathTimer - Конструктор по умолчанию (не доступен)
    ///
    DeathTimer();

    ///
    /// \brief ~DeathTimer - Виртуальный деструктор по умолчанию (не доступен)
    ///
    virtual ~DeathTimer() override = default;

public slots:

    ///
    /// \brief restart - Слот перезапустит таймер
    ///
    void restart();

private slots:

    ///
    /// \brief timeOut - Слот, обрабатывающий срабатывание таймера
    ///
    void timeOut();

};
//-----------------------------------------------------------------------------

#endif // DEATHTIMER_H
