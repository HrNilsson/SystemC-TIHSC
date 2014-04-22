//----------------------------------------------------------------------------------------------
// LmsFilter.h
//
//							Aarhus School of Engineering
//
//	Author: KBE / 2009.12.29
//----------------------------------------------------------------------------------------------
#ifndef LMS_FILTER_H_INCLUDED
#define LMS_FILTER_H_INCLUDED

// LMS filter
// Operates on integer format 1.15 presentation
// -------------------------------------------------------------------
// Adaptive filtering using LMS
// Aaptive filtering of the input sample x using the desired sample d
// The algorithm performs an adaptive FIR filtering on the input x
// The LMS algorithm updates the filter weights/coefficients 
// according to:
//   y(n) = w(n)*x(n) = sum{w(l)x(n-l)}  (FIR filter for l=1 to N)
//   e(n) = d(n)-y(n)                    (Estimation error)
//   w(k;n) = w(k;n-1)+f(k;x(n),e(n),u)  (LMS update of weights)
// where
//   f(k;x(n),e(n),x) = ue(n)x*(n-k) 
//
// Complex conjugate of the input vector, assuming only real value of x
//

// Initialization of LMS filter setting delayLine and coefficients buffer
void initLMSFilter(short *delayLine, short *weights, short length, short stepSize);
// delayLine - buffer to hold lenght of last samples
// weights - burrer to hold weights (FIR filter coefficients)
// length - size of filter weights and delayLine buffers
// stepSize - adaptation step size 


// Performs next step of LMS filtering and weights estimation
void LMSFilter(short x, short d, short *y, short *e);
// x - input sample (Must be normalized with peak(x) < 1)
// d - desired sample
// y - output sample
// e - error estimation sample

#endif // LMS_FILTER_H_INCLUDED
