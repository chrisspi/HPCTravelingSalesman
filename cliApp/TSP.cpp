#include <iostream>
#include <fstream>
#include <sstream>
#include "TSP.h"
using namespace std;

// constructor
// Checks whether file <filename> exists and can be opened
// Reads the file and shifts the content of the individual lines into a string
TSP::TSP(string filename){
    string line;
    vector<string> *tsp = new vector<string>;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
        tsp->push_back(line);
        }
        myfile.close();
    }

    else cout << "Unable to open file"; 

    // generates a city vector from the string vector
    parseTSP(tsp);
    // normalizes the coordinates in the city vector
    normaliseCities();
}

// Destruktor
TSP::~TSP(){
    delete cities;
}

// Returns a vector that contains the private coordinates of the cities
vector<City>* TSP::getCities(){
    return TSP::cities;
}

// 
int TSP::parseTSP(vector<string> *tsp){
    TSP::cities = new vector<City>;

    int mode = 0; //0 = Begin, 1= NODE_COORD_SECTION, 2 = EOF

    for(std::vector<string>::iterator line = tsp->begin(); line != tsp->end(); ++line) {
        if(mode == 0){
            if(!line->compare("NODE_COORD_SECTION")){
                mode = 1;
                continue;
            }     
        }
        else if(mode == 1){
            if(!line->compare("EOF")){
                mode = 2;
                continue;
            }

            string temp;
            stringstream lineStream ((*line));

            int count = 0;
            int index;
            double x,y;
            //Split values of line
            while (getline(lineStream, temp, ' ')) {
                if (!temp.compare(""))
                    continue;
                switch(count){
                    case 0: 
                        index = stoi(temp);
                        break;
                    case 1:
                        x = stod(temp);
                        break;
                    case 2:
                        y = stod(temp);
                        break;
                }  
                count++;
            }

            cities->push_back(City(x,y,index));
        }
    }

    delete tsp;
    return 0;
}


// Searches for the largest X and Y values in all cities
// then the coordinate values of the cities are divided by the maxima found
int TSP::normaliseCities(){
    //Translate Cities to positive space
    double minX = 0, minY = 0;
    for(std::vector<City>::iterator it = cities->begin(); it != cities->end(); ++it) {
           minX = min(minX,it->x);
           minY = min(minY,it->y);
    }

    //Find maximum X and Y Value
    double maxX = 0, maxY = 0;
    for(std::vector<City>::iterator it = cities->begin(); it != cities->end(); ++it) {
           it->x -= minX;
           it->y -= minY;
           
           maxX = max(maxX,it->x);
           maxY = max(maxY,it->y);
    }

    //Scale all points by the maximum Axis Value to fit in the [0,1] Space
    double maxAxis = max(maxX,maxY);
    for(std::vector<City>::iterator it = cities->begin(); it != cities->end(); ++it) {
           it->x /= maxAxis;
           it->y /= maxAxis;
    }

    TSP::scale = maxAxis;

    return 0;
}

double TSP::getScale(){
    return TSP::scale;
}
