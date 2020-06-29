#ifndef L1Algo_F64vec2P4_H
#define L1Algo_F64vec2P4_H

#include <iostream>
#include <cmath>
#include <emmintrin.h>
#include "vec_arithmetic.h"

/**********************************
 *
 *   Vector of four single doubles
 *
 **********************************/

//#pragma pack(push,16)/* Must ensure class & union 16-B aligned */

//typedef __m128d Vectordouble __attribute__ ((aligned(16)));

const union
{
  double d;
  long long i;
} __d_one = {(double)1.};

const union
{
    long long i[2];
    __m128d m;
} 
  __f64vec2_abs_mask_cheat = {{0x7fffffffffffffffll, 0x7fffffffffffffffll}},
  __f64vec2_sgn_mask_cheat = {{0x8000000000000000ull, 0x8000000000000000ull}},
  __f64vec2_zero_cheat     = {{         0,          0}},
  __f64vec2_one_cheat      = {{__d_one.i , __d_one.i }},
  __f64vec2_true_cheat     = {{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF}},
  __f64vec2_false_cheat    = {{0x0000000000000000, 0x0000000000000000}};

#define _f64vec2_abs_mask (static_cast<F64vec2>(__f64vec2_abs_mask_cheat.m))
#define _f64vec2_sgn_mask (static_cast<F64vec2>(__f64vec2_sgn_mask_cheat.m))
#define _f64vec2_zero     (static_cast<F64vec2>(__f64vec2_zero_cheat.m))
#define _f64vec2_one      (static_cast<F64vec2>(__f64vec2_one_cheat.m))
#define _f64vec2_true     (static_cast<F64vec2>(__f64vec2_true_cheat.m))
#define _f64vec2_false    (static_cast<F64vec2>(__f64vec2_false_cheat.m))

class F64vec2 
{
 public:

  __m128d v;

  double & operator[]( int i ){ return (reinterpret_cast<double*>(&v))[i]; }
  double   operator[]( int i ) const { return (reinterpret_cast<const double*>(&v))[i]; }

  F64vec2( ):v(_mm_set_pd1(0)){}
  F64vec2( const __m128d &a ):v(a) {}
  F64vec2( const double &a ):v(_mm_set_pd1(a)) {}

  F64vec2( const double &f0, const double &f1 ):v(_mm_set_pd(f1,f0)) {}

  /* Conversion function */
  operator  __m128d() const { return v; }		/* Convert to __m128d */

  /* Arithmetic Operators */
  friend F64vec2 operator +(const F64vec2 &a, const F64vec2 &b) { return _mm_add_pd(a,b); }
  friend F64vec2 operator -(const F64vec2 &a, const F64vec2 &b) { return _mm_sub_pd(a,b); } 
  friend F64vec2 operator *(const F64vec2 &a, const F64vec2 &b) { return _mm_mul_pd(a,b); } 
  friend F64vec2 operator /(const F64vec2 &a, const F64vec2 &b) { return _mm_div_pd(a,b); }

  /* Functions */
  friend F64vec2 min( const F64vec2 &a, const F64vec2 &b ){ return _mm_min_pd(a, b); }
  friend F64vec2 max( const F64vec2 &a, const F64vec2 &b ){ return _mm_max_pd(a, b); }

  /* Square Root */
  friend F64vec2 sqrt ( const F64vec2 &a ){ return _mm_sqrt_pd (a); }

  /* Reciprocal( inverse) Square Root */
  friend F64vec2 rsqrt( const F64vec2 &a ){ return 1./sqrt(a); }

  /* Reciprocal (inversion) */
  // friend F64vec2 rcp  ( const F64vec2 &a ){ return _mm_rcp_pd  (a); }
  /* Reciprocal (inversion) */
  //friend F64vec2 rcp  ( const F64vec2 &a ){ return 1. / a; }
  /* NewtonRaphson Reciprocal 
    [2 * rcppd(x) - (x * rcppd(x) * rcppd(x))] */
  friend F64vec2 rcp(const F64vec2 &a) {  return 1./a;  }


  /* Absolute value */
  friend F64vec2 fabs(const F64vec2 &a){ return _mm_and_pd(a, _f64vec2_abs_mask); }

  /* Sign */
  friend F64vec2 sgn(const F64vec2 &a){ return _mm_or_pd(_mm_and_pd(a, _f64vec2_sgn_mask),_f64vec2_one); }
  friend F64vec2 asgnb(const F64vec2 &a, const F64vec2 &b ){ 
    return _mm_or_pd(_mm_and_pd(b, _f64vec2_sgn_mask),a); 
  }

  /* Logical */
 
  friend F64vec2 operator&( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_and_pd(a, b);
  }
  friend F64vec2 operator|( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_or_pd(a, b);
  }
  friend F64vec2 operator^( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_xor_pd(a, b);
  }
  friend F64vec2 operator!( const F64vec2 &a ){ // mask returned
    return _mm_xor_pd(a, _f64vec2_true);
  }
  // friend F64vec2 operator||( const F64vec2 &a, const F64vec2 &b ){ // mask returned
  //   return _mm_or_pd(a, b);
  // }

  /* Comparison */

  friend F64vec2 operator<( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_cmplt_pd(a, b);
  }
  friend F64vec2 operator<=( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_cmple_pd(a, b);
  }
  friend F64vec2 operator>( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_cmpgt_pd(a, b);
  }
  friend F64vec2 operator>=( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_cmpge_pd(a, b);
  }
  friend F64vec2 operator==( const F64vec2 &a, const F64vec2 &b ){ // mask returned
    return _mm_cmpeq_pd(a, b);
  }

  #define if3(a, b, c)   ((a)&(b)) | ((!(a))&(c))    // analog (a) ? b : c

  #define NotEmpty(a)   bool((a)[0])|bool((a)[1])|bool((a)[2])|bool((a)[3])
  #define    Empty(a) !(bool((a)[0])|bool((a)[1])|bool((a)[2])|bool((a)[3]))
  // bool NotEmpty(const F64vec2 &a) { return a[0]||a[1]||a[2]||a[3]; }
  // bool    Empty(const F64vec2 &a) { return !(a[0]||a[1]||a[2]||a[3]); } // optimize
  friend F64vec2 bool2int( const F64vec2 &a){ // mask returned
    return if3(a,1,0);
  }
  
  /* Define all operators for consistensy */
  
  vec_arithmetic(F64vec2,double);

  /* Non intrinsic functions */

#define _f1(A,F) F64vec2( F(A[0]), F(A[1]) ) 

  friend F64vec2 exp( const F64vec2 &a ){ return _f1( a, exp ); } 
  friend F64vec2 log( const F64vec2 &a ){ return _f1( a, log ); } 
  friend F64vec2 sin( const F64vec2 &a ){ return _f1( a, sin ); } 
  friend F64vec2 cos( const F64vec2 &a ){ return _f1( a, cos ); } 
  friend F64vec2 acos( const F64vec2 &a ){ return _f1( a, acos ); } 

#undef _f1

  friend F64vec2 atan2(const F64vec2 &y, const F64vec2 &x) {
    const F64vec2 pi(3.1415926535897932);
    const F64vec2 pi_2 = pi/2;
    const F64vec2 zero(0);

    const F64vec2 &xZero = F64vec2(x == zero);
    const F64vec2 &yZero = F64vec2(y == zero);
    const F64vec2 &xNeg  = F64vec2(x < zero);
    const F64vec2 &yNeg  = F64vec2(y < zero);

    const F64vec2 &absX = fabs(x);
    const F64vec2 &absY = fabs(y);

    F64vec2 a = absY / absX;
    const F64vec2 pi_4 = pi/4;
    const F64vec2 &gt_tan_3pi_8 = F64vec2(a > F64vec2(2.414213562373095));
    const F64vec2 &gt_tan_pi_8  = F64vec2(a > F64vec2(0.4142135623730950)) & F64vec2(!gt_tan_3pi_8);
    const F64vec2 minusOne(-1);
    F64vec2 b(zero);
    b = (pi_2 & gt_tan_3pi_8) + (F64vec2(!gt_tan_3pi_8) & b);
    b = (pi_4 & gt_tan_pi_8) + (F64vec2(!gt_tan_pi_8) & b);
    a = (gt_tan_3pi_8 & (minusOne / a)) + (F64vec2(!gt_tan_3pi_8) & a);
    a = (gt_tan_pi_8 & ((absY - absX) / (absY + absX))) + (F64vec2(!gt_tan_pi_8) & a) ;
    const F64vec2 &a2 = a * a;
    b += (((8.05374449538e-2 * a2
          - 1.38776856032E-1) * a2
          + 1.99777106478E-1) * a2
          - 3.33329491539E-1) * a2 * a
          + a;
    F64vec2 xyNeg = F64vec2(xNeg ^ yNeg);
    b = (xyNeg & (-b) ) + (F64vec2(!xyNeg) & b);
    xyNeg = F64vec2(xNeg & !yNeg);
    b = (xyNeg & (b+pi)) + (F64vec2(!xyNeg) & b);
    xyNeg = F64vec2(xNeg &  yNeg);
    b = (xyNeg & (b-pi)) + (F64vec2(!xyNeg) & b);
    xyNeg = F64vec2(xZero & yZero);
    b = (xyNeg & zero) + (F64vec2(!xyNeg) & b);
    xyNeg = F64vec2(xZero &  yNeg);
    b = (xyNeg & (-pi_2)) + (F64vec2(!xyNeg) & b);
    return b;
  }

  friend std::ostream & operator<<(std::ostream &strm, const F64vec2 &a ){
    strm<<"["<<a[0]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<"]";
    return strm;
  }

  friend std::istream & operator>>(std::istream &strm, F64vec2 &a ){
    double tmp;
    strm>>tmp;
    a = tmp;
    return strm;
  }

} __attribute__ ((aligned(16)));


typedef F64vec2 fvec;
typedef double  fscal;
const int fvecLen = 2;
//#define fvec_true  _f64vec2_true
//#define fvec_false _f64vec2_false
#define _fvecalignment  __attribute__ ((aligned(16)))


#include "std_alloc.h"


#endif 
