#include <QApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "datasource.h"

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QQmlApplicationEngine applicationEngine;
    //QQuickStyle::setStyle("Material");

    DataSource dataSource;
    dataSource.setPath(QDir::home().path());

    applicationEngine.rootContext()->setContextProperty("DataSource", &dataSource);
    applicationEngine.rootContext()->setContextProperty("fsModel", &dataSource.model());
    applicationEngine.load(QUrl("qrc:/qml/forms/mainform.qml"));

    if (applicationEngine.rootObjects().isEmpty())
         return EXIT_FAILURE;
    else
        return application.exec();
}
//-----------------------------------------------------------------------------
