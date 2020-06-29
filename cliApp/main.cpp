#include <cmath>
#include <iostream>
// use math defines for getting pi as M_PI
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector> 
#include "tspvector.h"
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


	TSP travelingSalesman("berlin52.tsp");

	vector<City>* cities = travelingSalesman.getCities();

	// printing cities
    for(std::vector<City>::iterator it = cities->begin(); it != cities->end(); ++it) {
            cout << "City " << ":\t index:" << it->index << ",\t x:" << it->x << ", \t y:" << it->y << endl;
    }

	ENN network(cities);
    // dynamically allocate vector
    vector<NetworkPoint> *points = network.generateNetworkPoints(0.1, cities->size());

    // traverse points
    for(std::vector<NetworkPoint>::iterator it = points->begin(); it != points->end(); ++it) {
            cout << "Point " << it->index << ":\tx:" << it->x << ",\ty:" << it->y << endl;
    }

	network.optimizeNetworkPoints(20000);

	vector<int>* tspList = network.getTSPList();

	for(std::vector<int>::iterator it = tspList->begin(); it != tspList->end(); ++it) {
            cout << "City Index:  " << (*it) << endl;
    }

	cout << "Tour Length: " << network.getTourLength(travelingSalesman.getScale()) << endl;

    delete points; // delete points vector
}
