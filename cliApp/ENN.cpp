#define _USE_MATH_DEFINES
#include <cmath>
#include "ENN.h"

using namespace std;

ENN::ENN(std::vector<City>* cities, double alpha, double beta, double initialK, 
int KUpdatePeriod, double radius, double numPointFactor){
    ENN::alpha = alpha;
    ENN::beta = beta;
    ENN::initialK = initialK;
    ENN::KUpdatePeriod = KUpdatePeriod;
    ENN::radius = radius;
    ENN::numPointFactor = numPointFactor;
    ENN::cities = cities;

    int numpoints = cities->size() * ENN::numPointFactor;

    ENN::points = generateNetworkPoints(ENN::radius, numpoints);
}

vector<Point>* ENN::generateNetworkPoints(double radius, unsigned int numPoints){

    double deltaAngle = 2 * M_PI / numPoints;

    vector<Point> *points = new vector<Point>;
    // put all points into the points vector in form of a circle
    unsigned int count = 0;
	for (double angle = 0; angle <= 2*M_PI; angle+=deltaAngle) {
		points->push_back( Point( radius * cos( angle ) + 0.5,  radius * sin( angle ) + 0.5, count++) );
	}

    return points;
}

void ENN::optimizePoints(vector<Point> *points, vector<City> *cities){

}
