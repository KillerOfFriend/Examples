#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if (!w.initialize())
        return EXIT_FAILURE;
    else
    {
        w.show();
        return a.exec();
    }
}
