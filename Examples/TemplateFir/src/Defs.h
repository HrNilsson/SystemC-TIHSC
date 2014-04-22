#ifndef DEFS_H_
#define DEFS_H_
//============================================================================
// Name        : Defs.h
// Author      : Kim Bjerge
// Version     : 22. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized FIR filter design using templates
// 				 This is an untimed model
//				 Contains the global configurations parameters of the model
//============================================================================

#define TABS		23 // Number of taps in FIR filter
#define WBUS 		32 // Bus width
#define ALGO_BITS 	18 // Number of bits in sample

//------------------------------------------------------------------------------------------------

#if (ALGO_BITS == 16)
#define ALGO_SCALE		0x7fff     // 16 bit Maximum integer (15 bit + sign) value used for conversion float <-> fixed
#endif

#if (ALGO_BITS == 18)
#define ALGO_SCALE		0x1ffff    // 18 bit Maximum integer (17 bit + sign) value used for conversion float <-> fixed
#endif

#if (ALGO_BITS == 20)
#define ALGO_SCALE		0x7ffff   // 20 bit Maximum integer (19 bit + sign) value used for conversion float <-> fixed
#endif

#if (ALGO_BITS == 24)
#define ALGO_SCALE		0x7fffff  // 24 bit Maximum integer (23 bit + sign) value used for conversion float <-> fixed
#endif

#define float2fixed(i) ((int)(i*ALGO_SCALE))
#define fixed2float(i) ((double)i/ALGO_SCALE)


#endif /*DEFS_H_*/
