//----------------------------------------------------------------------------------------------
// IIRTest.cpp (systemc)
//
// Functional level for implemenentation of IIR filter
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include "Defs.h"
#include "IIRFilter.h"

// Create test file that contains a 500 Hz + 5 Khz sinus signal
void CreateTestFile(char *name, bool fixed = false)
{
	FILE *fp_out;    // Output test file
	int tmp_int;	 // Value fixed format
	float tmp_float; // Value float format

	// Create test file
	fp_out = fopen(name, "w");

	int n = 0;
	//int f1 = 20000;  // 500 Hz
	//int f2 = 50000; // 5000 Hz
	int f1 = 500;  // 500 Hz
	int f2 = 5000; // 5000 Hz

//#ifdef _TEST_SWEEP
#if 0
	// Creates 300 samples for each fc
	for (int n = 0; n < 840; n++)
	{ 
		f1 = (int)expf((float)n/100)+50;
		tmp_float = (float)sin((2*double_Pi/SAMPLE_FS)*f1*n)/2;

		if (fixed)
		{
			tmp_int = float2fixed(tmp_float);
			fprintf(fp_out, "%d\n", tmp_int);
		}
		else
		{
			fprintf(fp_out, "%f\n", tmp_float);
		}
	}

#else

	// Creates 1000 samples
	for (int n = 0; n < 1000; n++)
	{ 
		tmp_float = (float)sin((2*double_Pi/SAMPLE_FS)*f1*n)/4;
		tmp_float += (float)sin((2*double_Pi/SAMPLE_FS)*f2*n)/4;

		if (fixed)
		{
			tmp_int = float2fixed(tmp_float);
			fprintf(fp_out, "%d\n", tmp_int);
		}
		else
		{
			fprintf(fp_out, "%f\n", tmp_float);
		}
	}

#endif

	// Close test files
	fclose(fp_out);
}

// Test the IIR filter with floating point processing
void TestIIRFilterFunc(IIRFilter &IIR)
{
	FILE *fp_in;	 // Input test file
	FILE *fp_out;    // Output test file (floating point result)
	FILE *fp_out_fix;  // Output test file (fixed point result)
	int tmp_int;	 // Value fixed format
	float tmp_float; // Value float format

	// Open test files
	fp_in = fopen(INPUT_FILE_F, "r");
	fp_out = fopen(OUTPUT_FILE_F, "w");
	fp_out_fix = fopen(OUTPUT_FILE_FF, "w");

	while (fscanf(fp_in, "%f", &tmp_float) != EOF)
	{ 
		IIR.processSamples(&tmp_float, 1);
		fprintf(fp_out, "%f\n", tmp_float);
		tmp_int = float2fixed(tmp_float);
		fprintf(fp_out_fix, "%d\n", tmp_int);
	}

	// Close test files
	fclose(fp_in);
	fclose(fp_out);
	fclose(fp_out_fix);
}

// Test the IIR filter with fixed point processing
void TestIIRFilterArch(IIRFilter &IIR)
{
	FILE *fp_in;	 // Input test file
	FILE *fp_out;    // Output test file
	int tmp_int;	 // Value fixed format

	// Open test files
	fp_in = fopen(INPUT_FILE_A, "r");
	fp_out = fopen(OUTPUT_FILE_F, "w");

	while (fscanf(fp_in, "%d", &tmp_int) != EOF)
	{ 
		IIR.processSamples(&tmp_int, 1);
		fprintf(fp_out, "%d\n", tmp_int);
	}

	// Close test files
	fclose(fp_in);
	fclose(fp_out);
}


int main( int argc, char **argv)
{
	IIRFilter IIR;

	IIR.reset();
	//IIR.makeHighPass(SAMPLE_FS, TEST_FC);
	IIR.makeLowPass(SAMPLE_FS, TEST_FC); 
	//IIR.makeBandPass(SAMPLE_FS, TEST_FC, 10, 0.05); // Q = 10, Gain = 0.05
	//IIR.makeLowShelf(SAMPLE_FS, TEST_FC, 1, 0.1); // Q = 1, Gain = 0.1
	//IIR.makeHighShelf(SAMPLE_FS, TEST_FC, 1, 0.1); // Q = 1, Gain = 0.1

	// Functional test file (Float)
	CreateTestFile(INPUT_FILE_F); // Create floating point test file

	// Architecture test file (Fixed)
	CreateTestFile(INPUT_FILE_A, true); // Create fixed point test file

#if 1
	TestIIRFilterFunc(IIR);  // Make a IIR filter with fc = 1000 Hz, result as floating and fixed point
#else
	TestIIRFilterArch(IIR);  // Make a IIR fiter test in fixed point
#endif

	return 0;
}

