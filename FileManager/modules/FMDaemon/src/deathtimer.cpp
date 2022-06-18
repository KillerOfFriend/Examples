#include "deathtimer.h"

#include <QCoreApplication>

#include "dbus_defines.hpp"

//-----------------------------------------------------------------------------
DeathTimer::DeathTimer()
{
    connect(&m_timer, &QTimer::timeout, this, &DeathTimer::timeOut);
    restart();
}
//-----------------------------------------------------------------------------
DeathTimer& DeathTimer::Instance()
{
    static DeathTimer DT;
    return DT;
}
//-----------------------------------------------------------------------------
void DeathTimer::restart()
{
    m_timer.stop();
    m_timer.setSingleShot(true);
    m_timer.start(DBUS_SERVICE_LIFE);
}
//-----------------------------------------------------------------------------
void DeathTimer::timeOut()
{
    QCoreApplication::quit();
}
//-----------------------------------------------------------------------------
