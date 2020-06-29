#ifndef L1Algo_F32vec4P4_H
#define L1Algo_F32vec4P4_H

#include <iostream>
#include <cmath>
#include "xmmintrin.h"
#include "vec_arithmetic.h"

/**********************************
 *
 *   Vector of four single floats
 *
 **********************************/

//#pragma pack(push,16)/* Must ensure class & union 16-B aligned */

//typedef __m128 VectorFloat __attribute__ ((aligned(16)));

const union
{
  float f;
  int i;
} __f_one = {1.f};

const union
{
    int i[4];
    __m128 m;
} 
  __f32vec4_abs_mask_cheat = {{0x7fffffff, 0x7fffffff, 0x7fffffff, 0x7fffffff}},
  __f32vec4_sgn_mask_cheat = {{static_cast<int>(0x80000000), static_cast<int>(0x80000000), static_cast<int>(0x80000000), static_cast<int>(0x80000000)}},
  __f32vec4_zero_cheat     = {{         0,          0,          0,          0}},
  __f32vec4_one_cheat      = {{__f_one.i , __f_one.i , __f_one.i , __f_one.i }},
  __f32vec4_true_cheat     = {{static_cast<int>(0xFFFFFFFF), static_cast<int>(0xFFFFFFFF), static_cast<int>(0xFFFFFFFF), static_cast<int>(0xFFFFFFFF)}},
  __f32vec4_false_cheat    = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};

#define _f32vec4_abs_mask (static_cast<F32vec4>(__f32vec4_abs_mask_cheat.m))
#define _f32vec4_sgn_mask (static_cast<F32vec4>(__f32vec4_sgn_mask_cheat.m))
#define _f32vec4_zero     (static_cast<F32vec4>(__f32vec4_zero_cheat.m))
#define _f32vec4_one      (static_cast<F32vec4>(__f32vec4_one_cheat.m))
#define _f32vec4_true     (static_cast<F32vec4>(__f32vec4_true_cheat.m))
#define _f32vec4_false    (static_cast<F32vec4>(__f32vec4_false_cheat.m))

class F32vec4 
{
 public:

  __m128 v;

  float & operator[]( int i ){ return (reinterpret_cast<float*>(&v))[i]; }
  float   operator[]( int i ) const { return (reinterpret_cast<const float*>(&v))[i]; }

  F32vec4( ):v(_mm_set_ps1(0)){}
  F32vec4( const __m128 &a ):v(a) {}
  F32vec4( const float &a ):v(_mm_set_ps1(a)) {}

  F32vec4( const float &f0, const float &f1, const float &f2, const float &f3 ):v(_mm_set_ps(f3,f2,f1,f0)) {}

  /* Conversion function */
  operator  __m128() const { return v; }		/* Convert to __m128 */

  /* Arithmetic Operators */
  friend F32vec4 operator +(const F32vec4 &a, const F32vec4 &b) { return _mm_add_ps(a,b); }
  friend F32vec4 operator -(const F32vec4 &a, const F32vec4 &b) { return _mm_sub_ps(a,b); } 
  friend F32vec4 operator *(const F32vec4 &a, const F32vec4 &b) { return _mm_mul_ps(a,b); } 
  friend F32vec4 operator /(const F32vec4 &a, const F32vec4 &b) { return _mm_div_ps(a,b); }

  /* Functions */
  friend F32vec4 min( const F32vec4 &a, const F32vec4 &b ){ return _mm_min_ps(a, b); }
  friend F32vec4 max( const F32vec4 &a, const F32vec4 &b ){ return _mm_max_ps(a, b); }

  /* Square Root */
  friend F32vec4 sqrt ( const F32vec4 &a ){ return _mm_sqrt_ps (a); }

  /* Reciprocal( inverse) Square Root */
  friend F32vec4 rsqrt( const F32vec4 &a ){ return _mm_rsqrt_ps(a); }

  /* Reciprocal (inversion) */
  // friend F32vec4 rcp  ( const F32vec4 &a ){ return _mm_rcp_ps  (a); }
  /* Reciprocal (inversion) */
  //friend F32vec4 rcp  ( const F32vec4 &a ){ return 1. / a; }
  /* NewtonRaphson Reciprocal 
    [2 * rcpps(x) - (x * rcpps(x) * rcpps(x))] */
  friend F32vec4 rcp(const F32vec4 &a) {
    F32vec4 Ra0 = _mm_rcp_ps(a);
    return _mm_sub_ps(_mm_add_ps(Ra0, Ra0), _mm_mul_ps(_mm_mul_ps(Ra0, a), Ra0));
  }


  /* Absolute value */
  friend F32vec4 fabs(const F32vec4 &a){ return _mm_and_ps(a, _f32vec4_abs_mask); }

  /* Sign */
  friend F32vec4 sgn(const F32vec4 &a){ return _mm_or_ps(_mm_and_ps(a, _f32vec4_sgn_mask),_f32vec4_one); }
  friend F32vec4 asgnb(const F32vec4 &a, const F32vec4 &b ){ 
    return _mm_or_ps(_mm_and_ps(b, _f32vec4_sgn_mask),a); 
  }

  /* Logical */
 
  friend F32vec4 operator&( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_and_ps(a, b);
  }
  friend F32vec4 operator|( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_or_ps(a, b);
  }
  friend F32vec4 operator^( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_xor_ps(a, b);
  }
  friend F32vec4 operator!( const F32vec4 &a ){ // mask returned
    return _mm_xor_ps(a, _f32vec4_true);
  }
  // friend F32vec4 operator||( const F32vec4 &a, const F32vec4 &b ){ // mask returned
  //   return _mm_or_ps(a, b);
  // }

  /* Comparison */

  friend F32vec4 operator<( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_cmplt_ps(a, b);
  }
  friend F32vec4 operator<=( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_cmple_ps(a, b);
  }
  friend F32vec4 operator>( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_cmpgt_ps(a, b);
  }
  friend F32vec4 operator>=( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_cmpge_ps(a, b);
  }
  friend F32vec4 operator==( const F32vec4 &a, const F32vec4 &b ){ // mask returned
    return _mm_cmpeq_ps(a, b);
  }

  #define if3(a, b, c)   ((a)&(b)) | ((!(a))&(c))    // analog (a) ? b : c

  #define NotEmpty(a)   bool((a)[0])|bool((a)[1])|bool((a)[2])|bool((a)[3])
  #define    Empty(a) !(bool((a)[0])|bool((a)[1])|bool((a)[2])|bool((a)[3]))
  // bool NotEmpty(const F32vec4 &a) { return a[0]||a[1]||a[2]||a[3]; }
  // bool    Empty(const F32vec4 &a) { return !(a[0]||a[1]||a[2]||a[3]); } // optimize
  friend F32vec4 bool2int( const F32vec4 &a){ // mask returned
    return if3(a,1,0);
  }
  
  /* Define all operators for consistensy */
  
  vec_arithmetic(F32vec4,float);

  /* Non intrinsic functions */

#define _f1(A,F) F32vec4( F(A[0]), F(A[1]), F(A[2]), F(A[3]) ) 

  friend F32vec4 exp( const F32vec4 &a ){ return _f1( a, exp ); } 
  friend F32vec4 log( const F32vec4 &a ){ return _f1( a, log ); } 
  friend F32vec4 sin( const F32vec4 &a ){ return _f1( a, sin ); } 
  friend F32vec4 cos( const F32vec4 &a ){ return _f1( a, cos ); } 
  friend F32vec4 acos( const F32vec4 &a ){ return _f1( a, acos ); } 

#undef _f1

  friend F32vec4 atan2(const F32vec4 &y, const F32vec4 &x) {
    const F32vec4 pi(3.1415926535897932);
    const F32vec4 pi_2 = pi/2;
    const F32vec4 zero(0);

    const F32vec4 &xZero = F32vec4(x == zero);
    const F32vec4 &yZero = F32vec4(y == zero);
    const F32vec4 &xNeg  = F32vec4(x < zero);
    const F32vec4 &yNeg  = F32vec4(y < zero);

    const F32vec4 &absX = fabs(x);
    const F32vec4 &absY = fabs(y);

    F32vec4 a = absY / absX;
    const F32vec4 pi_4 = pi/4;
    const F32vec4 &gt_tan_3pi_8 = F32vec4(a > F32vec4(2.414213562373095));
    const F32vec4 &gt_tan_pi_8  = F32vec4(a > F32vec4(0.4142135623730950)) & F32vec4(!gt_tan_3pi_8);
    const F32vec4 minusOne(-1);
    F32vec4 b(zero);
    b = (pi_2 & gt_tan_3pi_8) + (F32vec4(!gt_tan_3pi_8) & b);
    b = (pi_4 & gt_tan_pi_8) + (F32vec4(!gt_tan_pi_8) & b);
    a = (gt_tan_3pi_8 & (minusOne / a)) + (F32vec4(!gt_tan_3pi_8) & a);
    a = (gt_tan_pi_8 & ((absY - absX) / (absY + absX))) + (F32vec4(!gt_tan_pi_8) & a) ;
    const F32vec4 &a2 = a * a;
    b += (((8.05374449538e-2 * a2
          - 1.38776856032E-1) * a2
          + 1.99777106478E-1) * a2
          - 3.33329491539E-1) * a2 * a
          + a;
    F32vec4 xyNeg = F32vec4(xNeg ^ yNeg);
    b = (xyNeg & (-b) ) + (F32vec4(!xyNeg) & b);
    xyNeg = F32vec4(xNeg & !yNeg);
    b = (xyNeg & (b+pi)) + (F32vec4(!xyNeg) & b);
    xyNeg = F32vec4(xNeg &  yNeg);
    b = (xyNeg & (b-pi)) + (F32vec4(!xyNeg) & b);
    xyNeg = F32vec4(xZero & yZero);
    b = (xyNeg & zero) + (F32vec4(!xyNeg) & b);
    xyNeg = F32vec4(xZero &  yNeg);
    b = (xyNeg & (-pi_2)) + (F32vec4(!xyNeg) & b);
    return b;
  }

  friend std::ostream & operator<<(std::ostream &strm, const F32vec4 &a ){
    strm<<"["<<a[0]<<" "<<a[1]<<" "<<a[2]<<" "<<a[3]<<"]";
    return strm;
  }

  friend std::istream & operator>>(std::istream &strm, F32vec4 &a ){
    float tmp;
    strm>>tmp;
    a = tmp;
    return strm;
  }

} __attribute__ ((aligned(16)));


typedef F32vec4 fvec;
typedef float  fscal;
const int fvecLen = 4;
//#define fvec_true  _f32vec4_true
//#define fvec_false _f32vec4_false
#define _fvecalignment  __attribute__ ((aligned(16)))


#include "std_alloc.h"


#endif 
