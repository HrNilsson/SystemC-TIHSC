/*
 ============================================================================
 Name        : LMSFilter.c
 Author      : Kim Bjerge
 Version     :
 Copyright   : Private
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Defs.h"
#include "LmsFilter.h"

#define NUM_SAMPLES 1000

// LMS Filter section
short LMSDelay[LMSLen];
short LMSWeights[LMSLen];

short d[NUM_SAMPLES] = {
						 #include "NoiseSignal.txt"
					   };
short x[NUM_SAMPLES]= {
						 #include "Noise.txt"
   	   	   	   	   	   };
short error[NUM_SAMPLES];

void initAdaptiveFilter(void)
{
   initLMSFilter(LMSDelay, LMSWeights, LMSLen, AdaptationStepSize);
}

int main(void) {
	int n;
	short output;
	FILE *fp_out;    // Output test file

	puts("Fixed Point version of LMS filter");
	fp_out = fopen("OutputSignal.txt", "w");

	initAdaptiveFilter();

	for (n = 0; n < NUM_SAMPLES; n++)
	{
		LMSFilter(x[n], d[n], &output, &error[n]);
		fprintf(fp_out, "%d\n", error[n]);
	}

	fclose(fp_out);
	puts("Filtered output signal created : OutputSignal.txt");

	return EXIT_SUCCESS;
}
