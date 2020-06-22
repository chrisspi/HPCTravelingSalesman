#include <cmath>
#include <iostream>
// use math defines for getting pi as M_PI
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector> 
#include "points.h"
#include "TSP.h"
#include "ENN.h"


using namespace std;

int main ( int argc, char *argv[]) {

	unsigned int numCitys = 10;
	const double PI = M_PI;
	const double radius = 0.1;
	const float numPointFactor = 2.5;
	unsigned int numPoints = numCitys * numPointFactor;
	double deltaAngle = 2*PI / numPoints;

    // output initial values
	cout << "Number of Citys: " << numCitys << endl;
	cout << "Radius: " << radius << endl;
	cout << "numPointFactor: " << numPointFactor << endl;
	cout << "Number of Points: numCitys * numPointFactor = " << numPoints << endl;
	cout << "Delta angle: " << deltaAngle << endl;
	cout << "\nInitial coordinates of points: " << endl;


	TSP travelingSalesman("ali535.tsp");

	vector<City>* cities = travelingSalesman.getCities();

	// printing cities
    for(std::vector<Point>::iterator it = cities->begin(); it != cities->end(); ++it) {
            cout << "City " << ":\t index:" << it->index << ",\t x:" << it->x << ", \t y:" << it->y << endl;
    }

	ENN network(cities);
    // dynamically allocate vector
    vector<Point> *points = network.generateNetworkPoints(0.1, cities->size());

    // traverse points
    for(std::vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {
            cout << "Point " << it->index << ":\tx:" << it->x << ",\ty:" << it->y << endl;
    }

	Point p1(1,1,0);
	Point p2(3,2,1);

	Point p3 = p1*2;

	cout << "Point " << p1.index << ":\tx:" << p1.x << ",\ty:" << p1.y << endl;
	cout << "Point " << p2.index << ":\tx:" << p2.x << ",\ty:" << p2.y << endl;
	cout << "Point " << p3.index << ":\tx:" << p3.x << ",\ty:" << p3.y << endl;

    delete points; // delete points vector
}
