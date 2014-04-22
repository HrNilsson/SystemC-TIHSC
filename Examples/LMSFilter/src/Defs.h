//----------------------------------------------------------------------------------------------
// Defs.h
//
//							Aarhus School of Engineering
//
//	Author: KBE / 2009.12.29
//----------------------------------------------------------------------------------------------
// User defines for HRV algorithm adjustment
#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

// Genneral HVR algorithm settings
#define SAMPLE_RATE			96000.0	// Sample rate in Hz

// LMS Filter section
#define LMSLen				128		// Length of LMS adaptive filter
#define AdaptationStepSize 	131	    // Format 1.15 with 0.004 (float)

#endif // DEFS_H_INCLUDED
