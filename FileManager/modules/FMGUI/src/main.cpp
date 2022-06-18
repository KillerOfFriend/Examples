#include <QApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "datasource.h"
#include "fsdbusadapter.h"


//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QQmlApplicationEngine applicationEngine;
    QQuickStyle::setStyle("Material");

    qmlRegisterType<FsDBusAdapter>("fsDBusAdapter", 1, 0, "FsDBusAdapter");

    DataSource dataSource; // Источник данных
    dataSource.setPath(QDir::home().path()); // Устанавливаем домашний каталог пользователя как текущую директорию
    // Пробросим в QML объекты управления
    applicationEngine.rootContext()->setContextProperty("DataSource", &dataSource);
    applicationEngine.rootContext()->setContextProperty("fsModel", &dataSource.model());
    // Загружаем главную форму из ресурса
    applicationEngine.load(QUrl("qrc:/qml/forms/mainform.qml"));
    // Проверяем успешнсто загрузки
    if (applicationEngine.rootObjects().isEmpty())
         return EXIT_FAILURE;
    else
        return application.exec();
}
//-----------------------------------------------------------------------------
