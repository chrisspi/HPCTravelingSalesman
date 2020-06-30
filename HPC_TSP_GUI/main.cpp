#include <QApplication>
#include "mainwindow.h"
#include "../cliApp/tspvector.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
/*
    TSPVector vec(0,4,0);
    TSPVector vec2(3,0,0);
    std::cout << "X: " << vec.x << " Y: " << vec.y << std::endl;
    std::cout << vec.magnitude() << std::endl;
    std::cout << "X: " << vec2.x << " Y: " << vec2.y << std::endl;
    std::cout << vec2.magnitude() << std::endl;
    vec += vec2;
    std::cout << "X: " << vec.x << " Y: " << vec.y << std::endl;
    std::cout << vec.magnitude() << std::endl;

    TSP tsp("/home/stefan/Dokumente/HPCTravelingSalesman/cliApp/berlin52.tsp");
    std::vector<City>* cities = tsp.getCities();
    for( int i = 0; i < cities->size(); i++ ) {
        std::cout << "X: " << cities->at(i).x << " Y: " << cities->at(i).y << std::endl;
        std::cout << cities->at(i).magnitude() << std::endl;
        }
*/
    
    return a.exec();
}
