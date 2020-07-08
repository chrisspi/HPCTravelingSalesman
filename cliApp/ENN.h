#include "tspvector.h"
#include <vector>
#include "omp.h"

//Define which Paralelization Settings are used, Comment out to not use them
#define SIMD
#define OPENMP

template<typename T>
class ENN{

    public:
        ENN(std::vector<City>* cities, double alpha = 1.0, double beta = 1.0, double initialK = 0.1, int KUpdatePeriod = 25, double radius = 0.1, double numPointFactor = 2.5);

        //Generates numPoints Network Points with the given radius around the center (0.5,0.5)
        std::vector<NetworkPoint<T>>* generateNetworkPoints(double radius, unsigned int numPoints);
        //Optimize Network Points for a single Iteration. Returns the updated NetworkPoints
        std::vector<NetworkPoint<T>>* optimizeNetworkPoints();
        //Optimize Network Points for the given Iterations. Returns the updated NetworkPoints
        std::vector<NetworkPoint<T>>* optimizeNetworkPoints(int iterations);
        //Returns an ordered List of the Cities for the current NetworkPoints
        std::vector<int>* getTSPList();
        double getTourLength(TSPVector<double> scale);
        std::vector<NetworkPoint<T>>* getNetworkPoints();
        
    private:
        double alpha;
        double beta;
        double K;
        int KUpdatePeriod;
        double radius;
        double numPointFactor;
        std::vector<City>* cities;
        std::vector<NetworkPoint<T>>* networkPoints;
        std::vector<NetworkPoint<T>> networkPointsCpy; //Copy of network Points at iteration start, sothat points are independent (OpenMP Requirement)
        double* v_ia_results;

        double getKNew();
        T v_ia(City& i, NetworkPoint<T>& a);
        T v_ia_helper(City& i, NetworkPoint<T>& a);
        Force<T> deltaY_a(NetworkPoint<T>& a);
        void calculateCityV_ia();

};

#include "ENN.cpp"