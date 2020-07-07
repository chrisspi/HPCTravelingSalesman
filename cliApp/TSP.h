#include "tspvector.h"
#include <string>
#include <vector> 

class TSP{
    public:
        TSP(std::string filename);
        ~TSP();
        //Returns List of normalised Cities of the given File
        std::vector<City>* getCities();
        TSPVector<double> getScale();

    private:
        TSPVector<double> scale;
        int parseTSP(std::vector<std::string> *tsp);
        std::vector<City> *cities;
        int normaliseCities();
};

#include "TSP.cpp"