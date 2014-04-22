#ifndef DEFS_H_
#define DEFS_H_
//============================================================================
// Name        : Defs.h
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector  design using templates
// 				 This is an untimed model
//				 Contains the global configurations parameters of the model
//============================================================================

#define WBUS 		32 		// Bus width
#define ALGO_BITS 	32 		// Number of bits in sample
#define WINDOW		1024 	// Window size for normalized squared difference function

// Configurations parameters for the pitch detector model
const int samples = 1024; 		// Number of samples 
const unsigned fs = 48000; 		// Sample frequence

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

#if (ALGO_BITS == 32)
#define ALGO_SCALE		0x7fffffff  // 32 bit Maximum integer (31 bit + sign) value used for conversion float <-> fixed
#endif

#define float2fixed(i) ((int)(i*ALGO_SCALE))
#define fixed2float(i) ((double)i/ALGO_SCALE)

#endif /*DEFS_H_*/
