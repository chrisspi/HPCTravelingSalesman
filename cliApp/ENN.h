#include "tspvector.h"
#include <vector>
template<typename T>
class ENN{

    public:
        ENN(std::vector<City<T>>* cities, double alpha = 1.0, double beta = 1.0, double initialK = 0.1, int KUpdatePeriod = 25, double radius = 0.1, double numPointFactor = 2.5);

        //Generates numPoints Network Points with the given radius around the center (0.5,0.5)
        std::vector<NetworkPoint<T>>* generateNetworkPoints(double radius, unsigned int numPoints);
        //Optimize Network Points for a single Iteration. Returns the updated NetworkPoints
        std::vector<NetworkPoint<T>>* optimizeNetworkPoints();
        //Optimize Network Points for the given Iterations. Returns the updated NetworkPoints
        std::vector<NetworkPoint<T>>* optimizeNetworkPoints(int iterations);
        //Returns an ordered List of the Cities for the current NetworkPoints
        std::vector<int>* getTSPList();
        double getTourLength(double scale);
        
    private:
        double alpha;
        double beta;
        double K;
        int KUpdatePeriod;
        double radius;
        double numPointFactor;
        std::vector<City<T>>* cities;
        std::vector<NetworkPoint<T>>* networkPoints;

        double* v_ia_results;

        double getKNew();
        double v_ia(City<T>& i, NetworkPoint<T>& a);
        double v_ia_helper(City<T>& i, NetworkPoint<T>& a);
        Force<T> deltaY_a(NetworkPoint<T>& a);
        void reset_via_results();

};

#include "ENN.cpp"