#include "observer.h"

#include <algorithm>

//-----------------------------------------------------------------------------
void Publisher::subscribe(std::shared_ptr<Subscriber> inNewSubscriber)
{
    if (inNewSubscriber)
        m_Subscribers.emplace_back(inNewSubscriber);
}
//-----------------------------------------------------------------------------
void Publisher::unsubscribe(std::shared_ptr<Subscriber> inSubscriber)
{
    auto FindRes = std::find_if(m_Subscribers.begin(), m_Subscribers.end(), [&inSubscriber](std::weak_ptr<Subscriber>& Item)
    {
        if (Item.expired())
            return false;
        else
            return Item.lock() == inSubscriber;
    });

    if (FindRes != m_Subscribers.end())
        m_Subscribers.erase(FindRes);
}
//-----------------------------------------------------------------------------
void Publisher::notify(std::uint32_t inEvent)
{
//    auto a = shared_from_this();
    auto It = m_Subscribers.begin();

    while (It != m_Subscribers.end()) // Перебираем подписчиков
    {
        if (It->expired()) // Подписчик уничтожен
            It = m_Subscribers.erase(It); // Отписываем
        else
        {
            It->lock()->update(shared_from_this(), inEvent); // Сообщаем о событии
            It++;
        }
    }
}
//-----------------------------------------------------------------------------
