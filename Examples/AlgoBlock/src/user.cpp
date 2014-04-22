//----------------------------------------------------------------------------------------------
// sink.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#include <systemc.h>
#include "user.h"
 
void user::GainTest(int &loops)
{
	// Printing peak each 1 ms periodes 

	// Set gain
	set_user.write(0); // Clear enable IIR filter bit
	set_gain.write(0);
	LogTxt("Gain : 0");
	WaitMs(10);
	
	LogTxt("Peak : " << get_peak.read());

	// Set gain
	set_gain.write(1);
	LogTxt("Gain : 1");
	WaitMs(10);

	LogTxt("Peak : " << get_peak.read());

	// Clear peak
	set_user.write(CLEAR_PEAK_BIT);
	LogTxt("Clear Peak");
	WaitMs(1);

	LogTxt("Peak : " << get_peak.read());

	// Set gain
	set_gain.write(2);
	LogTxt("Gain : 2");
	WaitMs(10);

	LogTxt("Loop " << loops++);

	WaitMs(1);
}

void user::SetCoefficients(void)
{
	// Set coefficients in algo
	set_coeff0.write(IIR.getCoeffFixed(0));
	set_coeff1.write(IIR.getCoeffFixed(1));
	set_coeff2.write(IIR.getCoeffFixed(2));
	set_coeff3.write(IIR.getCoeffFixed(4));
	set_coeff4.write(IIR.getCoeffFixed(5));
}

void user::Entry()
{
	int loops = 0;

	// Create IIR filter at Sample rate 44.1 kHz, fc = 1kHz
	//IIR.makeHighPass(SAMPLE_FS, TEST_FC); 
	IIR.makeLowPass(SAMPLE_FS, TEST_FC); 
	//IIR.makeBandPass(SAMPLE_FS, TEST_FC, 10, 0.05); // Q = 10, Gain = 0.05
	//IIR.makeLowShelf(SAMPLE_FS, TEST_FC, 1, 0.1); // Q = 1, Gain = 0.1
	//IIR.makeHighShelf(SAMPLE_FS, TEST_FC, 1, 0.1); // Q = 1, Gain = 0.1

	SetCoefficients();
	set_user.write(ENABLE_IIR_BIT);
	set_gain.write(1);
	LogTxt("Gain : 1");

	wait(CLK_PERIODE*5, SC_NS); // Wait for reset
	reset.write(false);  // Release reset

	while (true)
	{ 

#if 0
		GainTest(loops);
#else
		// Read peak
		WaitMs(1);
		LogTxt("Peak : " << get_peak.read());

		// Clear peak
		set_user.write(CLEAR_PEAK_BIT | ENABLE_IIR_BIT);
		wait(CLK_PERIODE*50, SC_NS);
		set_user.write(ENABLE_IIR_BIT);
#endif
	}
}
