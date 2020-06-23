#include <vector>
#include "points.h"
#include <vector>

class ENN{

    public:
        ENN(std::vector<City>* cities, double alpha = 1.0, double beta = 1.0, double initialK = 0.1, int KUpdatePeriod = 25, double radius = 0.1, double numPointFactor = 2.5);
        std::vector<Point>* generateNetworkPoints(double radius, unsigned int numPoints);
        void optimizePoints();
        std::vector<int>* getTSPList();
        
    private:
        double alpha;
        double beta;
        double K;
        int KUpdatePeriod;
        double radius;
        double numPointFactor;
        std::vector<City>* cities;
        std::vector<Point>* points;

        double getKNew();
        double v_ia(City& i, Point& a);
        double v_ia_helper(City& i, Point& a);
        Point deltaY_a(Point& a);

};