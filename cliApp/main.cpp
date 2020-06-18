#include <cmath>
#include <iostream>
// use math defines for getting pi as M_PI
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector> 
#include "points.h"

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

    // dynamically allocate vector
    vector<Point> *points = new vector<Point>;

    // put all points into the points vector in form of a circle
	for (double angle = 0; angle <= 2*PI; angle+=deltaAngle) {
		points->push_back( Point( radius * cos( angle ),  radius * sin( angle ) ) );
	}

	unsigned int pointCount = 0;
    // traverse points
    for(std::vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {
            cout << "Point " << pointCount++ << ":\tx:" << it->x << ",\ty:" << it->y << endl;
    }

    delete points; // delete points vector
}
