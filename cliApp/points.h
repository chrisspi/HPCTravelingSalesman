#include <cmath>

#ifndef TSPPOINT
#define TSPPOINT
struct Point {
     Point( double X, double Y , int Index): x(X), y(Y), index(Index) {};
     double x;
     double y;
     int index;

     double magnitude(){
          return sqrt(pow(x,2)+pow(y,2));
     }

     Point operator+(const Point& point){
          double x = this->x + point.x;
          double y = this->y + point.y;

          Point p(x,y,0);
          return p;
     }

     Point operator+=(const Point& point){
          x += point.x;
          y += point.y;

          return *this;
     }

     Point operator-(const Point& point){
          double x = this->x - point.x;
          double y = this->y - point.y;

          Point p(x,y,0);
          return p;
     }

     Point operator*(const double factor){
          double x = this->x * factor;
          double y = this->y * factor;

          Point p(x,y,0);
          return p; 
     }
};

typedef Point City;
typedef Point ForceDirection;
#endif
