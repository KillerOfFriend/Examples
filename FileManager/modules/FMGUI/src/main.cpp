#include <QApplication>
#include <QQuickStyle>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "models/fsmodel.h"

//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    FsModel fsModel;
    QDir currentDir = QDir::home();
    currentDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    fsModel.setDir(currentDir);

    QQmlApplicationEngine applicationEngine;
    QQuickStyle::setStyle("Material");

    applicationEngine.rootContext()->setContextProperty("fsModel", &fsModel);
    applicationEngine.load(QUrl("qrc:/qml/forms/mainform.qml"));

    return application.exec();
}
//-----------------------------------------------------------------------------
