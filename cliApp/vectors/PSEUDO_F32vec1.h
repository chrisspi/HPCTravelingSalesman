#ifndef CBM_KF_F32vec1_H
#define CBM_KF_F32vec1_H

#include <iostream>
#include <cmath>

/**********************************
 *
 *   Vector of one single float
 *
 **********************************/

// const union
// {
//     int i[1];
//     float m;
// } 
// __f32vec1_true_cheat     = {0xFFFFFFFF},
// __f32vec1_false_cheat    = {0x00000000};

// #define _f32vec1_true     ((F32vec1)__f32vec1_true_cheat.m)
// #define _f32vec1_false    ((F32vec1)__f32vec1_false_cheat.m)

class F32vec1 
{
 public:

  float v;

  float & operator[]( int i ){ return v;}
  float   operator[]( int i ) const { return v;}

  F32vec1( ){}
  F32vec1( const float &v0 ){ 
    v = v0;
  }

  /* Conversion function */
  operator  float() const { return v; }		/* Convert to __m128 */

  /* Arithmetic Operators */

  /* Functions */
  //friend F32vec1 min( const F32vec1 &a, const F32vec1 &b ){ return a<b ?a :b; }
  //friend F32vec1 max( const F32vec1 &a, const F32vec1 &b ){ return a>b ?a :b; }

  /* Square Root */

  /* Reciprocal( inverse) Square Root */
  //friend F32vec1 rsqrt( const F32vec1 &a ){ return 1./sqrt(a); }

  /* Reciprocal (inversion) */
  friend F32vec1 rcp  ( const F32vec1 &a ){ return 1./a; }

  /* Absolute value */
  //friend F32vec1 fabs(const F32vec1 &a){ return fabs(a); }

  /* Sign */
  //friend F32vec1 sgn(const F32vec1 &a){ return a<0 ?-1 :(a>0 ?1 :0); }

  /* Logical */
  /*
  friend F32vec1 operator&( const F32vec1 &a, const F32vec1 &b ){ // mask returned
    F32vec1 tmp;
    int *x = (int*)&tmp;
    int *y = (int*)&a;
    int *z = (int*)&b;
    x[0] = y[0] & z[0];
    x[1] = y[1] & z[1];
    return tmp;
  }
  */
  /* Non intrinsic functions */

  /* Define all operators for consistensy */
  
  friend void operator+=( F32vec1 &a, const F32vec1 &b ){ a = a + b ; } 
  friend void operator-=( F32vec1 &a, const F32vec1 &b ){ a = a - b ; } 
  friend void operator*=( F32vec1 &a, const F32vec1 &b ){ a = a * b ; } 
  friend void operator/=( F32vec1 &a, const F32vec1 &b ){ a = a / b ; } 

#define _op(A,B,O) F32vec1 z; z.v = A.v O B.v; return z; 
  
//   /* Comparison */
  friend F32vec1 operator <(const F32vec1 &a, const F32vec1 &b){ _op(a,b,<) }
  friend F32vec1 operator <=(const F32vec1 &a, const F32vec1 &b){ _op(a,b,<=) }
  friend F32vec1 operator >(const F32vec1 &a, const F32vec1 &b){ _op(a,b,>) }
  friend F32vec1 operator >=(const F32vec1 &a, const F32vec1 &b){ _op(a,b,>=) }

//   /* Logic */
  friend F32vec1 operator &(const F32vec1 &a, const F32vec1 &b){ _op(a,b,&&) }
  friend F32vec1 operator |(const F32vec1 &a, const F32vec1 &b){ _op(a,b,||) }
  friend F32vec1 operator ||(const F32vec1 &a, const F32vec1 &b){ _op(a,b,||) }
#undef _op
  
  friend F32vec1 operator !(const F32vec1 &a) {
    F32vec1 z;
    z[0] = !a[0];

    return z;
  }
  
  friend F32vec1 if3(const F32vec1 &a, const F32vec1 &b, const F32vec1 &c) {
    F32vec1 z;
    z[0] = (a[0]) ? b[0] : c[0];

    return z;
  }

#define NotEmpty(a)   bool((a)[0])
#define    Empty(a) !(bool((a)[0]))
  friend F32vec1 bool2int( const F32vec1 &a){ // mask returned
    return if3(a,1,0);
  }


  
  friend ostream & operator<<(ostream &strm, const F32vec1 &a ){
    strm<<a[0];
    return strm;
  }

  friend istream & operator>>(istream &strm, F32vec1 &a ){
    float tmp;
    strm>>tmp;
    a = tmp;
    return strm;
  }

} __attribute__ ((aligned(4)));;

typedef F32vec1 fvec;
const int fvecLen = 1;
// #define fvec_true  _f32vec1_true
// #define fvec_false _f32vec1_false
#define _fvecalignment  


namespace nsL1
{
      template<typename T>
      struct vector
      {
        typedef std::vector<T> TStd;
        typedef std::vector<T> TSimd;
      };
  
      typedef nsL1::vector<fvec>::TSimd vector_fvec;
}; // namespace nsL1

template<typename T>
struct nsL1vector: public nsL1::vector<T>  // just for use std::vector simultaniosly
{
};

#endif 
