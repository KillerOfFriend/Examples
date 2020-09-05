#ifndef OBSERVER_H
#define OBSERVER_H

#include <memory>
#include <vector>

class Publisher;

//-----------------------------------------------------------------------------
class Subscriber
{
public:

    /**
     * @brief Subscriber - Конструктор по умолчанию
     */
    Subscriber() = default;

    /**
     * @brief Subscriber - Виртуальный деструктор по умолчанию
     */
    virtual ~Subscriber() = default;

    /**
     * @brief update - Метод обработает событие от паблишера
     * @param inPublisher - Инициатор события
     * @param inEvent - Код события
     */
    virtual void update(std::shared_ptr<Publisher> inPublisher, std::uint32_t inEvent) = 0;

};
//-----------------------------------------------------------------------------
class Publisher : public std::enable_shared_from_this<Publisher>
{
public:

    /**
     * @brief Publisher - Конструктор по умолчанию
     */
    Publisher() = default;

    /**
     * @brief Publisher - Виртуальный деструктор по умолчанию
     */
    virtual ~Publisher() = default;

    /**
     * @brief subscribe - Метод добавит подписчика
     * @param inNewSubscriber - Новый подписчик
     */
    void subscribe(std::shared_ptr<Subscriber> inNewSubscriber);

    /**
     * @brief unsubscribe - Сетод удалит подписчика
     * @param inSubscriber - Подписчик
     */
    void unsubscribe(std::shared_ptr<Subscriber> inSubscriber);

protected:

    /**
     * @brief notify - Метод сообщит о собити подписчикам
     * @param inEvent - Код события
     */
    void notify(std::uint32_t inEvent);

private:
     std::vector<std::weak_ptr<Subscriber>> m_Subscribers; ///< Подписчики

};

//-----------------------------------------------------------------------------

#endif // OBSERVER_H
