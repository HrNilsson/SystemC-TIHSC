/** \file vector_td_operators.h
    \brief The class vector_td defines a D-dimensional vector of type T.

    The class vector_td defines a D-dimensional vector of type T.
    It is used in the Gadgetron to represent small (one- to four-dimensional) vectors only.
    For larger vectors consider using the NDArray class instead.
    The vector_td class can be used on both the cpu and gpu.
    The accompanying headers vector_td_opeators.h and vector_td_utilities.h define most of the functionality.
*/

#pragma once

#include "vector_td.h"
#include "core_defines.h"

namespace Gadgetron{

  //
  // Return types
  //

  template <class T, class I> struct vectorTDReturnType {};
  template <class T> struct vectorTDReturnType<T,T> { typedef T type;};
  template<> struct vectorTDReturnType<unsigned int, int> {typedef int type; };
  template<> struct vectorTDReturnType<float, float> {typedef float type; };
  template<> struct vectorTDReturnType<float, int> {typedef float type; };
  template<> struct vectorTDReturnType<int, float> {typedef float type; };
  template<> struct vectorTDReturnType<float, unsigned int> {typedef float type; };
  template<> struct vectorTDReturnType<unsigned int, float> {typedef float type; };
  template<> struct vectorTDReturnType<int, double> {typedef double type; };
  template<> struct vectorTDReturnType<double, int> {typedef double type; };
  template<> struct vectorTDReturnType<unsigned int, double> {typedef double type; };
  template<> struct vectorTDReturnType<double, unsigned int> {typedef double type; };
  template<> struct vectorTDReturnType<double, float> {typedef float type; };
  template<> struct vectorTDReturnType<float,double> {typedef float type; };

  //
  // Operators are defined as component wise operations.
  //

  //
  // Arithmetic operators
  //

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator+= ( vector_td<T,D> &v1, const vector_td<T,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] += v2.vec[i];
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator+= ( vector_td<T,D> &v1, const T &v2 )
  {
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] += v2;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator-= ( vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] -= v2.vec[i];
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator *= ( vector_td<T,D> &v1, const T &v2 )
  {
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] *= v2;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  void operator*= ( vector_td<T,D> &v1, const R &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] *= v2;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__
  void operator *=  ( vector_td<T,D> &v1, const vector_td<T,D> &v2 )
	{
      for(unsigned int i=0; i<D; i++ ) v1.vec[i] *= v2.vec[i];
    }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator /= ( vector_td<T,D> &v1, const T &v2 )
  {
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] /= v2;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__
  void operator /=  ( vector_td<T,D> &v1, const vector_td<T,D> &v2 )
  {
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] /= v2.vec[i];
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void component_wise_div_eq ( vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] /= v2.vec[i];
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator+ ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = v1.vec[i]+v2.vec[i];

    return res;
  }

  template< class T,class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator+ ( const vector_td<T,D> &v1, const R &v2 )
  {
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] =v1.vec[i]+v2;
    return res;
  }

  template< class T,class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator- ( const vector_td<T,D> &v1, const R &v2 )
  {
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] =v1.vec[i]-v2;
    return res;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator+ (const R &v2, const vector_td<T,D> &v1 )
  {
    return v1+v2;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator- ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = v1.vec[i]-v2.vec[i];
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> operator- ( const vector_td<T,D> &v1)
  {
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = -v1.vec[i];
    return res;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> component_wise_mul ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = v1.vec[i]*v2.vec[i];
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__
  vector_td<T,D> component_wise_mul ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 )
  {
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = v1.vec[i]*v2.vec[i];
    return res;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator* ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  {
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ )  res.vec[i]=v1.vec[i]*v2.vec[i];
    return res;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator* ( const vector_td<T,D> &v1, const R &v2 )
  { 
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ )  res.vec[i]=v1.vec[i]*v2;
    return res;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator* ( const R &v1, const vector_td<T,D> &v2 )
  { 
    return v2*v1;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator/ ( const vector_td<T,D> &v1, const R &v2 )
  {
    vector_td<typename vectorTDReturnType<T,R>::type,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i]=v1.vec[i]/v2;
    return res;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> operator/ ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  {
    vector_td<typename vectorTDReturnType<T,R>::type,D> res = v1;
    for(unsigned int i=0; i<D; i++ ) res[i] /= v2[i];
    return res;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  vector_td<typename vectorTDReturnType<T,R>::type,D> component_wise_div ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    return v1/v2;
  }

  // 
  // "Strong" comparison operators
  //

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  bool operator== ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    for(unsigned int i=0; i<D; i++ ) if(!(v1.vec[i] == v2.vec[i])) return false;
    return true;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  bool operator!= ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    for(unsigned int i=0; i<D; i++ ) if((v1.vec[i] != v2.vec[i])) return true;
    return false;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  bool operator&& ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    for(unsigned int i=0; i<D; i++ ) if(!(v1.vec[i] && v2.vec[i])) return false;
    return true;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  bool operator|| ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    for(unsigned int i=0; i<D; i++ ) if(!(v1.vec[i] || v2.vec[i])) return false;
    return true;
  }

  template< class T,class R, unsigned int D > __inline__ __host__ __device__ 
  bool operator< ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(!(v1.vec[i] < v2.vec[i])) return false;
    return true;
  }

  template< class T,class R, unsigned int D > __inline__ __host__ __device__
  bool operator<= ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(!(v1.vec[i] <= v2.vec[i])) return false;
    return true;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  bool operator> ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(!(v1.vec[i] > v2.vec[i])) return false;
    return true;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  bool operator>= ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(!(v1.vec[i] >= v2.vec[i])) return false;
    return true;
  }

  //
  // "Weak" comparison "operators"
  //

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  bool weak_equal ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] == v2.vec[i]) return true;
    return false;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__
  bool weak_not_equal ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] != v2.vec[i]) return true;
    return false;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__
  bool weak_and ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] && v2.vec[i]) return true;
    return false;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  bool weak_or ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] || v2.vec[i]) return true;
    return false;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  bool weak_less ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] < v2.vec[i]) return true;
    return false;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  bool weak_less_equal ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] <= v2.vec[i]) return true;
    return false;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__
  bool weak_greater ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] > v2.vec[i]) return true;
    return false;
  }

  template< class T, class R, unsigned int D > __inline__ __host__ __device__ 
  bool weak_greater_equal ( const vector_td<T,D> &v1, const vector_td<R,D> &v2 )
  { 
    for(unsigned int i=0; i<D; i++ ) if(v1.vec[i] >= v2.vec[i]) return true;
    return false;
  }

  //
  // Vector comparison "operators"
  //

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_equal ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] == v2.vec[i]);
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_not_equal ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] != v2.vec[i]);
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_and ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] && v2.vec[i]);
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_or ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] || v2.vec[i]);
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_less ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] < v2.vec[i]);
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_less_equal ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] <= v2.vec[i]);
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_greater ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  {
    vector_td<T,D> res; 
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] > v2.vec[i]);
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> vector_greater_equal ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  {  
    vector_td<T,D> res;
    for(unsigned int i=0; i<D; i++ ) res.vec[i] = (v1.vec[i] >= v2.vec[i]);
    return res;
  }

  //
  // Integer only operators
  //

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator<<= ( vector_td<T,D> &v1, unsigned int shifts ) 
  { 
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] <<= shifts;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator>>= ( vector_td<T,D> &v1, unsigned int shifts ) 
  { 
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] >>= shifts;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> operator<< ( const vector_td<T,D> &v1, unsigned int shifts ) 
  { 
    vector_td<T,D> res = v1;
    res <<= shifts;
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> operator>> ( const vector_td<T,D> &v1, unsigned int shifts ) 
  { 
    vector_td<T,D> res = v1;
    res >>= shifts;
    return res;
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  void operator%= ( vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    for(unsigned int i=0; i<D; i++ ) v1.vec[i] %= v2.vec[i];
  }

  template< class T, unsigned int D > __inline__ __host__ __device__ 
  vector_td<T,D> operator% ( const vector_td<T,D> &v1, const vector_td<T,D> &v2 ) 
  { 
    vector_td<T,D> res = v1;
    res %= v2;
    return res;
  }
}
