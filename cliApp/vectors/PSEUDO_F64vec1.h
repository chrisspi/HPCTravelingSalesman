#ifndef L1Algo_PSEUDO_F64vec1_H
#define L1Algo_PSEUDO_F64vec1_H

#include <iostream>
#include <cmath>
#include "vec_arithmetic.h"

/**********************************
 *
 *   Vector of four doubles
 *
 **********************************/

class F64vec1 
{
 public:

  double v[1];

  double & operator[]( int i ){ return ((double*)&v)[i]; }
  double   operator[]( int i ) const { return ((double*)&v)[i]; }

  F64vec1( ){}
  F64vec1( const F64vec1 &a ) { 
    v[0] = a.v[0]; 
  }
  F64vec1( const double &a ) { 
    v[0] = a; 
  }

  friend double min( double x, double y ){ return x<y ?x :y; }
  friend double max( double x, double y ){ return x<y ?y :x; }
  friend double asgnb( double x, double y ){ return y>=0 ?fabs(x) :-fabs(x); }
  friend double rsqrt( double x ){ return 1./sqrt(x); }
  friend double rcp( double x ){ return 1./x; }
  friend double sgn( double x ){ return x>=0 ?1 :-1; }

#define _f2(A,B,F) F64vec1 z; z.v[0] = F(A.v[0],B.v[0]); return z;
#define _f1(A,F)   F64vec1 z; z.v[0] = F(A.v[0]); return z;
#define _op(A,B,O) F64vec1 z; z.v[0] = A.v[0] O B.v[0]; return z; 

  /* Arithmetic Operators */
  friend F64vec1 operator +(const F64vec1 &a, const F64vec1 &b){ _op(a,b,+) }
  friend F64vec1 operator -(const F64vec1 &a, const F64vec1 &b){ _op(a,b,-) }
  friend F64vec1 operator *(const F64vec1 &a, const F64vec1 &b){ _op(a,b,*) }
  friend F64vec1 operator /(const F64vec1 &a, const F64vec1 &b){ _op(a,b,/) }

  /* Functions */
  friend F64vec1 min( const F64vec1 &a, const F64vec1 &b ){ _f2(a,b,min) }
  friend F64vec1 max( const F64vec1 &a, const F64vec1 &b ){ _f2(a,b,max) }
  friend F64vec1 asgnb( const F64vec1 &a, const F64vec1 &b ){ _f2(a,b,asgnb) }
  friend F64vec1 sqrt ( const F64vec1 &a ){ _f1(a,sqrt) }
  friend F64vec1 rsqrt( const F64vec1 &a ){ _f1(a,rsqrt) }
  friend F64vec1 rcp  ( const F64vec1 &a ){ _f1(a,rcp) }
  friend F64vec1 fabs (const F64vec1 &a) { _f1(a,fabs) }
  friend F64vec1 sgn  ( const F64vec1 &a ){ _f1(a,sgn) }
  friend F64vec1 exp( const F64vec1 &a ){ _f1(a,exp) } 
  friend F64vec1 log( const F64vec1 &a ){ _f1(a,log) } 
  friend F64vec1 sin( const F64vec1 &a ){ _f1(a,sin) } 
  friend F64vec1 cos( const F64vec1 &a ){ _f1(a,cos) } 
#undef _f1
#undef _f2
#undef _op

  /* Define all operators for consistensy */
  
  vec_arithmetic(F64vec1,double);

  friend std::ostream & operator<<(std::ostream &strm, const F64vec1 &a ){
    strm<<a[0];
    return strm;
  }

  friend std::istream & operator>>(std::istream &strm, F64vec1 &a ){
    double tmp;
    strm>>tmp;
    a = tmp;
    return strm;
  }

};// __attribute__ ((aligned(16)));;

typedef F64vec1 fvec;
const int fvecLen = 1;
typedef double  fscal;

//#define fvec_true  _f32vec1_true
//#define fvec_false _f32vec1_false
#define _fvecalignment  


#endif 
