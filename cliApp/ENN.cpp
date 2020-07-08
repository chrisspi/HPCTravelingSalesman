#define _USE_MATH_DEFINES
#include <cmath>
#include <list>
#include <algorithm>
#include <iostream>

using namespace std;

template<typename T>
ENN<T>::ENN(std::vector<City>* cities, double alpha, double beta, double initialK, 
int KUpdatePeriod, double radius, double numPointFactor){
    ENN::alpha = alpha;
    ENN::beta = beta;
    ENN::K = initialK;
    ENN::KUpdatePeriod = KUpdatePeriod;
    ENN::radius = radius;
    ENN::numPointFactor = numPointFactor;
    ENN::cities = cities;

    int numpoints = cities->size() * ENN::numPointFactor;

    numpoints += numpoints % 4; //Muss durch 4 teilbar sein

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
       #ifdef SIMD
        float* xFvec = new float[4];
        float* yFvec = new float[4];
        for(int i=0; i< 4; i++){
            xFvec[i] = radius * cos( angle ) + 0.5;
            yFvec[i] = radius * sin( angle ) + 0.5;
            if(i != 3) angle += deltaAngle;
        }  

        NetworkPoint<fvec> np(fvec(xFvec[0],xFvec[1],xFvec[2],xFvec[3]),fvec(yFvec[0],yFvec[1],yFvec[2],yFvec[3]),count++);

        points->push_back(np);

        #else
        points->push_back( NetworkPoint<double>( radius * cos( angle ) + 0.5,  radius * sin( angle ) + 0.5, count++) );
        #endif
        
	}
    return points;
}

template <typename T>
vector<NetworkPoint<T>>* ENN<T>::optimizeNetworkPoints(int iterations){
    for(int i=0; i<iterations; i++){
        //std::cout << "Iteration:" << i << std::endl;

        optimizeNetworkPoints();
    }

    return ENN::networkPoints;
}

template <typename T>
vector<NetworkPoint<T>>* ENN<T>::optimizeNetworkPoints(){
    ENN::calculateCityV_ia();

    ENN::networkPointsCpy = *ENN::networkPoints;

    #ifdef OPENMP
    #pragma omp parallel for num_threads(omp_get_num_procs()) 
    #endif
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
T ENN<T>::v_ia(City& i, NetworkPoint<T>& a){
    T upper = ENN::v_ia_helper(i,a);

    double lower = ENN::v_ia_results[i.index-1];

    return upper/lower;
}

template <typename T>
T ENN<T>::v_ia_helper(City& i, NetworkPoint<T>& a){
    double t = 2 * pow(K,2);

    T mag = (i-a).magnitude();

    T sum_1 = -(mag*mag)/t;
    T sum = exp(sum_1);

    return sum;
}

template <typename T>
Force<T> ENN<T>::deltaY_a(NetworkPoint<T>& a){
    Force<T> cityForceSum(0,0,0);

    for(vector<City>::iterator it = ENN::cities->begin(); it != ENN::cities->end(); ++it) {
        cityForceSum += (*it - a) * v_ia(*it,a);
    }

    Force<T> cityForce = cityForceSum * ENN::alpha;


    NetworkPoint<T>* a_prev = &(ENN::networkPoints->back());
    NetworkPoint<T>* a_next;
    for(typename vector<NetworkPoint<T>>::iterator it = ENN::networkPointsCpy.begin(); it != ENN::networkPointsCpy.end(); ++it) {
        if(it->index == a.index){
            ++it;
            if(it != ENN::networkPointsCpy.end()) a_next = &(*it);
            else a_next = &(*ENN::networkPointsCpy.begin());

            break;
        }
        a_prev = &(*it);

    }

    #ifdef SIMD
    NetworkPoint<fvec> a_prevShifted(fvec(a_prev->x[3],a.x[0],a.x[1],a.x[2]),fvec(a_prev->y[3],a.y[0],a.y[1],a.y[2]),0);
    NetworkPoint<fvec> a_nextShifted(fvec(a.x[1],a.x[2],a.x[3],a_next->x[0]),fvec(a.y[1],a.y[2],a.y[3],a_next->y[0]),0);

    a_prev = &a_prevShifted;
    a_next = &a_nextShifted;
    #endif

    Force<T> pointForce =  (*a_prev + *a_next - (a * 2)) * ENN::beta * ENN::K;

    return cityForce + pointForce;
}

template <typename T>
std::vector<int>* ENN<T>::getTSPList(){

    //Todo: Change to get nearest Point from every city to sort cities, instead nearest city for every point
    std::vector<int> *tspList = new std::vector<int>;
    for(typename vector<NetworkPoint<T>>::iterator itP = ENN::networkPoints->begin(); itP != ENN::networkPoints->end(); ++itP) {
        double shortestDistance = 2;
        City* nearestCity;
        for(vector<City>::iterator itC = ENN::cities->begin(); itC != ENN::cities->end(); ++itC) {
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
double ENN<T>::getTourLength(TSPVector<double> scale){
    double length = 0;

    NetworkPoint<T>& prevPoint = networkPoints->back();
    #ifdef SIMD
    NetworkPoint<double> prevPointSIMD(prevPoint.x[3],prevPoint.y[3],0);
    #endif
    for(typename vector<NetworkPoint<T>>::iterator itP = ENN::networkPoints->begin(); itP != ENN::networkPoints->end(); ++itP) {
        #ifdef SIMD
        for(int i=0; i<4; i++){
            NetworkPoint<double> tempNP(itP->x[i],itP->y[i],0);

            length += (prevPointSIMD * scale - tempNP * scale).magnitude();
            prevPointSIMD = tempNP;
        }
        #else
        length += (prevPoint * scale - *itP * scale).magnitude();
        prevPoint = *itP;
        #endif
    }

    return length;
}

template <typename T>
void ENN<T>::calculateCityV_ia(){
    #ifdef OPENMP
    #pragma omp parallel for num_threads(omp_get_num_procs())
    #endif
    for(vector<City>::iterator itC = ENN::cities->begin(); itC != ENN::cities->end(); ++itC) {
        T lower(0);
        for(typename vector<NetworkPoint<T>>::iterator it = ENN::networkPoints->begin(); it != ENN::networkPoints->end(); ++it) {
            lower += v_ia_helper(*itC,*it);
        }
        #ifdef SIMD
        ENN::v_ia_results[itC->index-1] = lower[0] + lower[1] + lower[2] + lower[3];
        #else
        ENN::v_ia_results[itC->index-1] = lower;
        #endif
    }
}

template <typename T>
std::vector<NetworkPoint<T>>* ENN<T>::getNetworkPoints(){
    return ENN::networkPoints;
}

