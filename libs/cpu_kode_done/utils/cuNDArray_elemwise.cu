#include "cuNDArray_elemwise.h"
#include "cuNDArray_operators.h"
#include "complext.h"

#include <complex>
#include <thrust/functional.h>

using namespace std;
 
namespace Gadgetron{

  template<typename T> struct cuNDA_real : public thrust::unary_function<T,typename realType<T>::Type>
  {
    __device__ typename realType<T>::Type operator()(const T &x) const {return real(x);}
  };
  
  template<class T> boost::shared_ptr< cuNDArray<typename realType<T>::Type> > 
  real( cuNDArray<T> *x )
  { 
    if( x == 0x0 )
      throw std::runtime_error("Gadgetron::real(): Invalid input array");
    
    boost::shared_ptr< cuNDArray<typename realType<T>::Type> > result(new cuNDArray<typename realType<T>::Type>());
    result->create(x->get_dimensions());
    thrust::device_ptr<typename realType<T>::Type> resPtr = result->get_device_ptr();
    thrust::device_ptr<T> xPtr = x->get_device_ptr();
    thrust::transform(xPtr,xPtr+x->get_number_of_elements(),resPtr,cuNDA_real<T>());
    return result;
  }
  
  template <typename T> struct cuNDA_imag : public thrust::unary_function<T,typename realType<T>::Type>
  {
    __device__ typename realType<T>::Type operator()(const T &x) const {return imag(x);}
  };
  
  template<class T> boost::shared_ptr< cuNDArray<typename realType<T>::Type> > 
  imag( cuNDArray<T> *x )
  { 
    if( x == 0x0 )
      throw std::runtime_error("Gadgetron::imag(): Invalid input array");
    
    boost::shared_ptr< cuNDArray<typename realType<T>::Type> > result(new cuNDArray<typename realType<T>::Type>());
    result->create(x->get_dimensions());
    thrust::device_ptr<typename realType<T>::Type> resPtr = result->get_device_ptr();
    thrust::device_ptr<T> xPtr = x->get_device_ptr();
    thrust::transform(xPtr,xPtr+x->get_number_of_elements(),resPtr,cuNDA_imag<T>());
    return result;
  }
  
  
  template <typename T> struct cuNDA_real_to_complex : public thrust::unary_function<typename realType<T>::Type,T>
  {
    __device__ T operator()(const typename realType<T>::Type &x) const {return T(x);}
  };
  
  template<class T> boost::shared_ptr< cuNDArray<T> > 
  real_to_complex( cuNDArray<typename realType<T>::Type> *x )
  {
    if( x == 0x0 )
      throw std::runtime_error("Gadgetron::real_to_complex(): Invalid input array");
    
    boost::shared_ptr< cuNDArray<T> > result(new cuNDArray<T>());
    result->create(x->get_dimensions());
    thrust::device_ptr<T> resPtr = result->get_device_ptr();
    thrust::device_ptr<typename realType<T>::Type> xPtr = x->get_device_ptr();
    thrust::transform(xPtr,xPtr+x->get_number_of_elements(),resPtr,cuNDA_real_to_complex<T>());
    return result;
  }

  //
  // Instantiation
  //
  
  template EXPORTGPUCORE boost::shared_ptr< cuNDArray<float> > real<float_complext>( cuNDArray<float_complext>* );
  
  template EXPORTGPUCORE boost::shared_ptr< cuNDArray<float> > imag<float_complext>( cuNDArray<float_complext>* );
  
  template EXPORTGPUCORE boost::shared_ptr< cuNDArray<float_complext> > real_to_complex<float_complext>( cuNDArray<float>* );
}

