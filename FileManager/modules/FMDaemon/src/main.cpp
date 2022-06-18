#include <QCoreApplication>
#include <QDBusConnection>
#include <QDebug>

#include "dbus_defines.hpp"
#include "dbus_fshelper.h"
#include "deathtimer.h"

//-----------------------------------------------------------------------------
int main (int argc, char * argv[])
{
    int Result = EXIT_SUCCESS;
    QCoreApplication a(argc, argv);
    fs::DBusFsHelper Helper;
    // Запускаем таймер "самоуничтожения"
    QObject::connect(&Helper, &fs::DBusFsHelper::actionDone, &DeathTimer::Instance(), &DeathTimer::restart);
    // Регистрируем объект
    if(!QDBusConnection::sessionBus().registerObject(DBUS_OBJECT_NAME, &Helper, QDBusConnection::ExportAllSlots))
    {
        qCritical() << "Can't register object";
        Result = EXIT_FAILURE;
    }
    else
    {
        qDebug() << "Connected to D-bus";
        // Регистрируем сервис
        if (!QDBusConnection::sessionBus().registerService(DBUS_SERVICE_NAME))
        {
            qCritical() << QDBusConnection::sessionBus().lastError().message();
            Result = EXIT_FAILURE;
        }
        else
        {
            qDebug() << "Service start";
            Result = a.exec();
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
