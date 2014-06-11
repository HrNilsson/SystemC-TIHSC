/** \file cuNDArray_elemwise.h
    \brief Element-wise math operations on the cuNDArray class.

    !!!
    This file has been stripped for the DPC course. 
    We only need the float  float <-> complex conversion utilities
    !!!
*/

#pragma once

#include "cuNDArray.h"
#include "gpucore_export.h"

namespace Gadgetron{

  /**
   * @brief Extract the real component from a complex array.
   * @param[in] x Input array.
   * @return A new array of the real component of the complex array.
   */
  template<class T> EXPORTGPUCORE boost::shared_ptr< cuNDArray<typename realType<T>::Type> > real( cuNDArray<T> *x );

  /**
   * @brief Extract the imaginary component from a complex array.
   * @param[in] x Input array.
   * @return A new array of the imaginary component of the complex array.
   */
  template<class T> EXPORTGPUCORE boost::shared_ptr< cuNDArray<typename realType<T>::Type> > imag( cuNDArray<T> *x );

  /**
   * @brief Construct a complex array from a real array.
   * @param[in] x Input array.
   * @return A new complex array containing the input array in the real component and zeros in the imaginary component.
   */
  template<class T> EXPORTGPUCORE boost::shared_ptr< cuNDArray<T> > real_to_complex( cuNDArray<typename realType<T>::Type> *x ); 
}
