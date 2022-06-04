#include <QApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "models/fsmodel.h"

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QQmlApplicationEngine applicationEngine;

    QQuickStyle::setStyle("Material");
    applicationEngine.load(QUrl("qrc:/qml/forms/mainform.qml"));

    FsModel fsModel;
    QDir currentDir = QDir::home();
    currentDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    fsModel.setDir(currentDir);

    applicationEngine.rootContext()->setContextProperty("fsModel", &fsModel);


    return application.exec();
}
//-----------------------------------------------------------------------------
