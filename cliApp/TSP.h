#ifndef TSPGUARD
#define TSPGUARD
#include <iostream>
#include <fstream>
#include <sstream>
#include "tspvector.h"
#include <string>
#include <vector> 

class TSP{
    public:
        TSP(std::string filename);
        ~TSP();
        //Returns List of normalised Cities of the given File
        std::vector<City>* getCities();
        TSPVector getScale();

    private:
        TSPVector scale;
        int parseTSP(std::vector<std::string> *tsp);
        std::vector<City> *cities;
        int normaliseCities();
};
#endif
