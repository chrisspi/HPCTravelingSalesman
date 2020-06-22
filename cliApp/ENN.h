#include <vector>
#include "points.h"
#include <vector>

class ENN{

    public:
        ENN(std::vector<City>* cities, double alpha = 1.0, double beta = 1.0, double initialK = 0.1, int KUpdatePeriod = 25, double radius = 0.1, double numPointFactor = 2.5);
        std::vector<Point>* generateNetworkPoints(double radius, unsigned int numPoints);
        void optimizePoints(std::vector<Point>* points,std::vector<City>* cities);
        
    private:
        double alpha;
        double beta;
        double initialK;
        int KUpdatePeriod;
        double radius;
        double numPointFactor;
        std::vector<City>* cities;
        std::vector<Point>* points;

};