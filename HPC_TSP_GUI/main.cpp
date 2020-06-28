#include <QApplication>
#include "mainwindow.h"
#include "../cliApp/tspvector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    TSPVector vec(1,0,0);

    vec.magnitude();
    
    return a.exec();
}
