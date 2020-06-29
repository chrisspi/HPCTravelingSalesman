#include <cmath>
#include <iostream>
// use math defines for getting pi as M_PI
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector> 
#include "tspvector.h"
#include "TSP.h"
// #include "TSP.cpp"
#include "ENN.h"
// #include "ENN.cpp"
#include "TStopwatch.h"
#include "vectors/P4_F32vec4.h"

typedef fvec DataType;
 
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


	TSP<DataType> travelingSalesman("berlin52.tsp");

	vector<City<DataType>>* cities = travelingSalesman.getCities();

	// printing cities
    for(std::vector<City<DataType>>::iterator it = cities->begin(); it != cities->end(); ++it) {
            cout << "City " << ":\t index:" << it->index << ",\t x:" << it->x << ", \t y:" << it->y << endl;
    }

	ENN<DataType> network(cities);
    // dynamically allocate vector
    vector<NetworkPoint<DataType>> *points = network.generateNetworkPoints(0.1, cities->size());

    // traverse points
    for(std::vector<NetworkPoint<DataType>>::iterator it = points->begin(); it != points->end(); ++it) {
            cout << "Point " << it->index << ":\tx:" << it->x << ",\ty:" << it->y << endl;
    }

	TStopwatch timerScalar;
	network.optimizeNetworkPoints(100);
	timerScalar.Stop();

	// vector<int>* tspList = network.getTSPList();

	// for(std::vector<int>::iterator it = tspList->begin(); it != tspList->end(); ++it) {
            // cout << "City Index:  " << (*it) << endl;
    // }

	double tScal = timerScalar.RealTime()*1000;
	cout << "Tour Length: " << network.getTourLength(travelingSalesman.getScale()) << endl;
	cout << "Time scalar: " << tScal << " ms " << endl;

    delete points; // delete points vector
}
