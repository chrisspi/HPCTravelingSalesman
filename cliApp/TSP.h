#include "tspvector.h"
#include <string>
#include <vector> 

template<typename T>
class TSP{
    public:
        TSP(std::string filename);
        ~TSP();
        //Returns List of normalised Cities of the given File
        std::vector<City<T>>* getCities();
        double getScale();

    private:
        double scale;
        int parseTSP(std::vector<std::string> *tsp);
        std::vector<City<T>> *cities;
        int normaliseCities();
};

#include "TSP.cpp"