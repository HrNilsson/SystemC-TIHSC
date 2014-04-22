//----------------------------------------------------------------------------------------------
// LmsFilter.c
//
//							Aarhus School of Engineering
//
//	Author: KBE / 2009.12.29
//----------------------------------------------------------------------------------------------
// LMS filter
#include "Defs.h"
#include "LmsFilter.h"

static short   L;   		// Length of LMS filter (buffers below)
static short   *delay; 	    // Delay line of x
static short   *w;  		// Weights/filter coefficients
static short   u;   		// Adaptation step size

// Initialization of LMS filter setting delayLine and coefficients buffer
void initLMSFilter(short *delayLine, short *weights, short length, short stepSize)
{
	short k;
	
	delay = delayLine;
	w = weights;
	L = length;
	u = stepSize;
	
	// Clear weights and delay line
	for (k = 0; k < L; k++)
	{
		w[k] = 0;
		delay[k] = 0;
	}
	
} 

void LMSFilter(short x, short d, short *y, short *e)
{
    int yn=0, wk_i;
    short k;
    short out, err, wk_s;
    
    short len = L;  		// For optimization
    short *dly = delay; 	// For optimization
    short *wgt = w;			// For optimization
    short adpt = u;			// For optimization

    // Shift delay line
   for(k=len-1; k > 0; k--)
        dly[k] = dly[k-1];

    // Insert next x
    dly[0] = x;

    // Convolution: w * x
    for(k=0; k < len; k++)
        yn += wgt[k] * dly[k];

    // Calculate output result
    out = (yn >> 15);
    
    // Estimate error (n)
    err = d - out;
       
    // Adjust weights
    for(k=0; k < len; k++)
    {
       wk_i = err*dly[k];
       wk_s = (wk_i >> 15); // Truncate
       wk_i = adpt*wk_s;  
       wgt[k] += (wk_i >> 15); // Truncate
    }
    
    // Return output and error estimate
    *y = out;
    *e = err;
}
