#define _USE_MATH_DEFINES
#include <cmath>
#include "ENN.h"
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

ENN::ENN(std::vector<City>* cities, double alpha, double beta, double initialK, 
int KUpdatePeriod, double radius, double numPointFactor){
    ENN::alpha = alpha;
    ENN::beta = beta;
    ENN::K = initialK;
    ENN::KUpdatePeriod = KUpdatePeriod;
    ENN::radius = radius;
    ENN::numPointFactor = numPointFactor;
    ENN::cities = cities;

    int numpoints = cities->size() * ENN::numPointFactor;

    ENN::networkPoints = generateNetworkPoints(ENN::radius, numpoints);
}

vector<NetworkPoint>* ENN::generateNetworkPoints(double radius, unsigned int numPoints){

    double deltaAngle = 2 * M_PI / numPoints;

    vector<NetworkPoint> *points = new vector<NetworkPoint>;
    // put all points into the points vector in form of a circle
    unsigned int count = 0;
	for (double angle = 0; angle <= 2*M_PI; angle+=deltaAngle) {
		points->push_back( NetworkPoint( radius * cos( angle ) + 0.5,  radius * sin( angle ) + 0.5, count++) );
	}

    return points;
}

vector<NetworkPoint>* ENN::optimizeNetworkPoints(int iterations){
    for(int i=0; i<iterations; i++){
        std::cout << "Iteration:" << i << std::endl;

        optimizeNetworkPoints();
    }

    return ENN::networkPoints;
}

vector<NetworkPoint>* ENN::optimizeNetworkPoints(){
    for(std::vector<NetworkPoint>::iterator it = ENN::networkPoints->begin(); it != ENN::networkPoints->end(); ++it) {
        (*it) += deltaY_a(*it);
    }
    
    ENN::K = ENN::getKNew();

    return ENN::networkPoints;
}

double ENN::getKNew(){
    double kNew = max(0.01, 0.99*K);

    return kNew;
}

double ENN::v_ia(City& i, NetworkPoint& a){
    double upper = ENN::v_ia_helper(i,a);

    double lower = 0;
    for(std::vector<NetworkPoint>::iterator it = ENN::networkPoints->begin(); it != ENN::networkPoints->end(); ++it) {
        lower += v_ia_helper(i,*it);
    }

    return upper/lower;
}

double ENN::v_ia_helper(City& i, NetworkPoint& a){
    double T = 2 * pow(K,2);

    double sum_1 = (-pow((i-a).magnitude(),2))/T;
    double sum = pow(M_E,sum_1);

    return sum;
}

Force ENN::deltaY_a(NetworkPoint& a){
    Force cityForceSum(0,0,0);

    for(std::vector<City>::iterator it = ENN::cities->begin(); it != ENN::cities->end(); ++it) {
        cityForceSum += (*it - a) * v_ia(*it,a);
    }

    Force cityForce = cityForceSum * ENN::alpha;


    NetworkPoint* a_prev = &(ENN::networkPoints->back());
    NetworkPoint* a_next;
    for(std::vector<NetworkPoint>::iterator it = ENN::networkPoints->begin(); it != ENN::networkPoints->end(); ++it) {
        if(it->index == a.index){
            ++it;
            if(it != ENN::networkPoints->end()) a_next = &(*it);
            else a_next = &(*ENN::networkPoints->begin());

            // if(!a_prev) a_prev = &(ENN::points->back());

            break;
        }
        a_prev = &(*it);

    }

    Force pointForce =  (*a_prev + *a_next - (a * 2)) * ENN::beta * ENN::K;

    return cityForce + pointForce;
}

std::vector<int>* ENN::getTSPList(){

    //Todo: Change to get nearest Point from every city to sort cities, instead nearest city for every point
    

    std::vector<int> *tspList = new std::vector<int>;
    for(std::vector<NetworkPoint>::iterator itP = ENN::networkPoints->begin(); itP != ENN::networkPoints->end(); ++itP) {
        double shortestDistance = 2;
        City* nearestCity;
        for(std::vector<City>::iterator itC = ENN::cities->begin(); itC != ENN::cities->end(); ++itC) {
            double distance = ((*itC)-(*itP)).magnitude();

            if(distance < shortestDistance){
                shortestDistance = distance;
                nearestCity = &(*itC);
            }
        }

        if(std::find(tspList->begin(), tspList->end(), nearestCity->index) == tspList->end()) {
            tspList->push_back(nearestCity->index);
        }
    }

    return tspList;
}
