#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
ENN<T>::ENN(std::vector<City<T>>* cities, double alpha, double beta, double initialK, 
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

    ENN::v_ia_results = new double[ENN::cities->size()];
}

template <typename T>
vector<NetworkPoint<T>>* ENN<T>::generateNetworkPoints(double radius, unsigned int numPoints){

    double deltaAngle = 2 * M_PI / numPoints;

    vector<NetworkPoint<T>> *points = new vector<NetworkPoint<T>>;
    // put all points into the points vector in form of a circle
    unsigned int count = 0;
	for (double angle = 0; angle <= 2*M_PI; angle+=deltaAngle) {
		points->push_back( NetworkPoint<T>( radius * cos( angle ) + 0.5,  radius * sin( angle ) + 0.5, count++) );
	}

    return points;
}
template <typename T>
vector<NetworkPoint<T>>* ENN<T>::optimizeNetworkPoints(int iterations){
    for(int i=0; i<iterations; i++){
        std::cout << "Iteration:" << i << std::endl;

        optimizeNetworkPoints();
    }

    return ENN::networkPoints;
}

template <typename T>
vector<NetworkPoint<T>>* ENN<T>::optimizeNetworkPoints(){
    ENN::reset_via_results();

    for(typename vector<NetworkPoint<T>>::iterator it = ENN::networkPoints->begin(); it != ENN::networkPoints->end(); ++it) {
        (*it) += deltaY_a(*it);
    }
    ENN::K = ENN::getKNew();

    return ENN::networkPoints;
}

template <typename T>
double ENN<T>::getKNew(){
    double kNew = max(0.01, 0.99*K);

    return kNew;
}

template <typename T>
double ENN<T>::v_ia(City<T>& i, NetworkPoint<T>& a){
    double upper = ENN::v_ia_helper(i,a);

    double lower = ENN::v_ia_results[i.index-1];
    if(lower == -9999){
        lower = 0;
        for(typename vector<NetworkPoint<T>>::iterator it = ENN::networkPoints->begin(); it != ENN::networkPoints->end(); ++it) {
            lower += v_ia_helper(i,*it);
        }
        ENN::v_ia_results[i.index-1] = lower;
    }
    

    return upper/lower;
}

template <typename T>
double ENN<T>::v_ia_helper(City<T>& i, NetworkPoint<T>& a){
    double t = 2 * pow(K,2);

    double sum_1 = (-pow((i-a).magnitude(),2))/t;
    double sum = pow(M_E,sum_1);

    return sum;
}

template <typename T>
Force<T> ENN<T>::deltaY_a(NetworkPoint<T>& a){
    Force<T> cityForceSum(0,0,0);

    for(typename vector<City<T>>::iterator it = ENN::cities->begin(); it != ENN::cities->end(); ++it) {
        cityForceSum += (*it - a) * v_ia(*it,a);
    }

    Force<T> cityForce = cityForceSum * ENN::alpha;


    NetworkPoint<T>* a_prev = &(ENN::networkPoints->back());
    NetworkPoint<T>* a_next;
    for(typename vector<NetworkPoint<T>>::iterator it = ENN::networkPoints->begin(); it != ENN::networkPoints->end(); ++it) {
        if(it->index == a.index){
            ++it;
            if(it != ENN::networkPoints->end()) a_next = &(*it);
            else a_next = &(*ENN::networkPoints->begin());

            // if(!a_prev) a_prev = &(ENN::points->back());

            break;
        }
        a_prev = &(*it);

    }

    Force<T> pointForce =  (*a_prev + *a_next - (a * 2)) * ENN::beta * ENN::K;

    return cityForce + pointForce;
}

template <typename T>
std::vector<int>* ENN<T>::getTSPList(){

    //Todo: Change to get nearest Point from every city to sort cities, instead nearest city for every point
    std::vector<int> *tspList = new std::vector<int>;
    for(typename vector<NetworkPoint<T>>::iterator itP = ENN::networkPoints->begin(); itP != ENN::networkPoints->end(); ++itP) {
        double shortestDistance = 2;
        City<T>* nearestCity;
        for(typename vector<City<T>>::iterator itC = ENN::cities->begin(); itC != ENN::cities->end(); ++itC) {
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
template <typename T>
double ENN<T>::getTourLength(double scale){
    double length = 0;

    NetworkPoint<T>& prevPoint = networkPoints->back();
    for(typename vector<NetworkPoint<T>>::iterator itP = ENN::networkPoints->begin(); itP != ENN::networkPoints->end(); ++itP) {
        length += (prevPoint - *itP).magnitude();
        prevPoint = *itP;
    }

    return length * scale;
}

template <typename T>
void ENN<T>::reset_via_results(){
    for(int i=0; i<cities->size(); i++){
        ENN::v_ia_results[i] = -9999;
    }
}
