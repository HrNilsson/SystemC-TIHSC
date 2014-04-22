//============================================================================
// Name        : Top.cpp
// Author      : Kim Bjerge
// Version     : 26. April 2011
// Copyright   : IHA
// Description : Example of a parameterized design using templates
//               Contains the top level design 
//				 at functional and architecture level
//============================================================================
#include "Top.h"
				 
 //----------------------------------------------------------------------------
 // Top level testbench for FIR filter
 //----------------------------------------------------------------------------
Top::Top(sc_module_name name) : 
		sc_module(name),
		input_1k("input_1k"),
		input_2k("input_2k"),
		input_3k("input_3k"),
		mix_out("mix_out"),
		fir_in("fir_in"),
		monitor_in("monitor_in"),
		output("output"),
		src_sine_1k("sine_1k", samples, 1000, fs), // 1 khz sin
		src_sine_2k("sine_2k", samples, 2000, fs), // 2 khz sine
		src_sine_3k("sine_3k", samples, 3000, fs), // 3 khz sine
		mix("mixer", 0.2), // Gain = 0.5
		fork("fork"),
		monitor_mix("monitor_mix", samples, mix_file, false),
		monitor_ref("monitor_ref", samples, ref_file)
{
	// Connect signal generator 1 kHz sine
	src_sine_1k.out(input_1k);

	// Connect signal generator 2 kHz sine
	src_sine_2k.out(input_2k);

	// Connect signal generator 3 kHz sine
	src_sine_3k.out(input_3k);
	
	// Connect Mixer to add the sine signals together
	mix.in(input_1k);
	mix.in(input_2k);
	mix.in(input_3k);
	mix.out(mix_out);

	// Split the mixed signal in 2 
	fork.in(mix_out);
	fork.out(monitor_in);
	fork.out(fir_in);
	
	// Monitor of mixed input result
	monitor_mix.in(monitor_in);
		
	FirCoeff_if<double> *pFirCoeff;	

#ifdef _HIGH_PASS
	pFirCoeff = new HighPassFir<double, taps>(fs, fc); // HighPass 2 khz
	pFir = new ParFir<fir_T, taps>("fir",  pFirCoeff->GetCoeffs());
#else
	pFirCoeff = new LowPassFir<double, taps>(fs, fc); // LowPass 2 khz
	pFir = new ParFir<fir_T, taps>("fir",  pFirCoeff->GetCoeffs());
#endif
	
	pFir->in(fir_in);
	pFir->out(output);

	// Monitor of filtered output result
	monitor_ref.in(output);	
	
}
