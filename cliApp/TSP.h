#include "points.h"
#include <string>
#include <vector> 

class TSP{
    public:
        TSP(std::string filename);
        ~TSP();
        std::vector<City>* getCities();

    private:
        int parseTSP(std::vector<std::string> *tsp);
        std::vector<City> *cities;
        int normaliseCities();
};