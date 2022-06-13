#include <QApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "datasource.h"
#include "fshelper.h"

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QQmlApplicationEngine applicationEngine;
    //QQuickStyle::setStyle("Material");

    FsHelper Helper; // Интерфейс взаимодействия с демоном
    DataSource dataSource; // Источник данных
    dataSource.setPath(QDir::home().path()); // Устанавливаем домашний каталог пользователя как текущую директорию
    // Пробросим в QML объекты управления
    applicationEngine.rootContext()->setContextProperty("DataSource", &dataSource);
    applicationEngine.rootContext()->setContextProperty("fsModel", &dataSource.model());
    applicationEngine.rootContext()->setContextProperty("Helper", &Helper);
    // Загружаем главную форму из ресурса
    applicationEngine.load(QUrl("qrc:/qml/forms/mainform.qml"));
    // Проверяем успешнсто загрузки
    if (applicationEngine.rootObjects().isEmpty())
         return EXIT_FAILURE;
    else
        return application.exec();
}
//-----------------------------------------------------------------------------
