#include <cmath>
#include <iostream>
#ifndef TSPVECTOR
#define TSPVECTOR


struct TSPVector {
     TSPVector( double X, double Y , int Index): x(X), y(Y), index(Index) {};
     double x;
     double y;
     int index;

     double magnitude(){
          return sqrt(pow(x,2)+pow(y,2));
     }

     TSPVector operator+(const TSPVector& point){
          double x = this->x + point.x;
          double y = this->y + point.y;

          TSPVector p(x,y,0);
          return p;
     }

     TSPVector operator+=(const TSPVector& point){
          x += point.x;
          y += point.y;

          return *this;
     }

     
     TSPVector operator-(const TSPVector& point){
          double x = this->x - point.x;
          double y = this->y - point.y;

          TSPVector p(x,y,0);
          return p;
     }

     TSPVector operator*(const TSPVector& point){
          double x = this->x * point.x;
          double y = this->y * point.y;

          TSPVector p(x,y,0);
          return p;
     }

     TSPVector operator-=(const TSPVector& point){
          x -= point.x;
          y -= point.y;

          return *this;
     }
     
     
     TSPVector operator*(const double factor){
          double x = this->x * factor;
          double y = this->y * factor;

          TSPVector p(x,y,0);
          return p; 
     }
          
     TSPVector operator*=(const TSPVector& point){
          x += point.x;
          y += point.y;

          return *this;
     }
     
     
};

typedef TSPVector City;
typedef TSPVector Force;
typedef TSPVector NetworkPoint;
#endif
