#include <cmath>

#ifndef TSPVECTOR
#define TSPVECTOR

template <typename T> 
struct TSPVector {
     TSPVector( T X, T Y , int Index): x(X), y(Y), index(Index) {};
     T x;
     T y;
     int index;

     T magnitude(){
          return sqrt(x * x + y * y);
     }

     TSPVector operator+(const TSPVector& point){
          T x = this->x + point.x;
          T y = this->y + point.y;

          TSPVector p(x,y,0);
          return p;
     }

     TSPVector operator+=(const TSPVector& point){
          x += point.x;
          y += point.y;

          return *this;
     }

     
     TSPVector operator-(const TSPVector& point){
          T x = this->x - point.x;
          T y = this->y - point.y;

          TSPVector p(x,y,0);
          return p;
     }

     TSPVector operator-=(const TSPVector& point){
          x -= point.x;
          y -= point.y;

          return *this;
     }
     
     
     TSPVector operator*(const double factor){
          T x = this->x * factor;
          T y = this->y * factor;

          TSPVector p(x,y,0);
          return p; 
     }
          
     TSPVector operator*=(const TSPVector& point){
          x += point.x;
          y += point.y;

          return *this;
     }
     
     
};

template<typename T>
     using City = TSPVector<T>;
template<typename T>
     using Force = TSPVector<T>;
template<typename T>
     using NetworkPoint = TSPVector<T>;

// typedef TSPVector<T> City;
// typedef TSPVector<T> Force;
// typedef TSPVector<T> NetworkPoint;
#endif
