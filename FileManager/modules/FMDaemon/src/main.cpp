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

    if (!QDBusConnection::sessionBus().isConnected())
    {
        Result = EXIT_FAILURE;
        qCritical() << QObject::tr("DBus connection fail!");
    }
    else
    {
        QDBusConnectionInterface* DBusInterface = QDBusConnection::sessionBus().interface();

        if(DBusInterface->registeredServiceNames().value().contains(DBUS_SERVICE_NAME)) // Сервис уже зарегестрирован
        {
            Result = EXIT_FAILURE;
            qCritical() << QObject::tr("Service already started!");
        }
        else
        {
            // Инициализируем функционал хелпера
            fs::DBusFsHelper Helper;
            // Запускаем таймер "самоуничтожения"
            QObject::connect(&Helper, &fs::DBusFsHelper::actionDone, &DeathTimer::Instance(), &DeathTimer::restart);
            // Регистрируем объект
            if(!QDBusConnection::sessionBus().registerObject(DBUS_OBJECT_NAME, &Helper, QDBusConnection::ExportAllSlots))
            {
                Result = EXIT_FAILURE;
                qCritical() << QObject::tr("Can't register object!");
            }
            else
            {
                qDebug() << QObject::tr("Connected to D-bus");
                // Регистрируем сервис
                if (!QDBusConnection::sessionBus().registerService(DBUS_SERVICE_NAME))
                {
                    Result = EXIT_FAILURE;
                    qCritical() << QDBusConnection::sessionBus().lastError().message();
                }
                else
                {
                    QCoreApplication a(argc, argv);
                    qDebug() << QObject::tr("Service started");
                    Result = a.exec();
                }
            }
        }
    }

    return Result;
}
//-----------------------------------------------------------------------------
