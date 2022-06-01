#include <QApplication>
#include <QQuickStyle>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QQmlApplicationEngine applicationEngine;

    QQuickStyle::setStyle("Material");
    applicationEngine.load(QUrl("qrc:/qml/mainform.qml"));

    return application.exec();
}
