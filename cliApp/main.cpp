#include <iostream>
#include <math.h>

using namespace std;

int main ( int argc, char *argv[]) {

	unsigned int numCitys = 10;
	const double PI = 3.14159;
	const double radius = 0.1;
	const float numPointFactor = 2.5;
	unsigned int numPoints = numCitys * numPointFactor;
	double deltaAngle = 2*PI / numPoints;

	cout << "Number of Citys: " << numCitys << endl;
	cout << "Radius: " << radius << endl;
	cout << "numPointFactor: " << numPointFactor << endl;
	cout << "Number of Points: numCitys * numPointFactor = " << numPoints << endl;
	cout << "Delta angle: " << deltaAngle << endl;
	cout << "\nInitial coordinates of points: " << endl;

	unsigned int count = 0;
	for (double angle = 0; angle <= 2*PI; angle+=deltaAngle) {
		cout << count++ << ": x = "<< radius * cos( angle ) << ", \ty = " << radius * sin( angle ) << endl;
	}

}
