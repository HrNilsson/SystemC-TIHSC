//============================================================================
// Name        : Top.cpp
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector  design using templates
//               Contains the top level design 
//				 at functional and architecture level
//============================================================================
#include "Top.h"

//#define SC_ARCHITECTURE

// Name of monitor files
const std::string mix_file("mix_file.txt");
const std::string acf_file("acf_file.txt");
			 
 //----------------------------------------------------------------------------
 // Top level testbench for FIR filter
 //----------------------------------------------------------------------------
Top::Top(sc_module_name name) : 
		sc_module(name),
		input_1("input_1"),
		input_2("input_2"),
		input_3("input_3"),
		mix_out("mix_out"),
		algo_in("algo_in"),
		monitor_in("monitor_in"),
		output("output"),
		acf_out("acf_out"),
		src_sine_1("sine_1", samples, 50, fs, 0.5),  // 50 Hz sin
		src_sine_2("sine_2", samples, 100, fs, 0.3), // 100 Hz sine
		src_sine_3("sine_3", samples, 200, fs, 0.3), // 200 Hz sine
/*
		src_sine_1("sine_1", samples, 100, fs, 0.5),  // 50 Hz sin
		src_sine_2("sine_2", samples, 200, fs, 0.3), // 100 Hz sine
		src_sine_3("sine_3", samples, 400, fs, 0.3), // 200 Hz sine
		src_sine_1("sine_1", samples, 1000, fs, 0.5),  // 50 Hz sin
		src_sine_2("sine_2", samples, 2000, fs, 0.3), // 100 Hz sine
		src_sine_3("sine_3", samples, 4000, fs, 0.3), // 200 Hz sine
		src_sine_1("sine_1", samples, 4000, fs, 0.5),  // 50 Hz sin
		src_sine_2("sine_2", samples, 8000, fs, 0.3), // 100 Hz sine
		src_sine_3("sine_3", samples, 16000, fs, 0.3), // 200 Hz sine
*/
		mix("mixer", 1.0), // Gain = 0.5
		fork("fork"),

#ifdef SC_ARCHITECTURE
		monitor_mix("monitor_mix", samples, mix_file, false)
#else
	    monitor_mix("monitor_mix", samples, mix_file, false),
		monitor_ref("monitor_ref", samples, ref_file),
		monitor_acf("monitor_acf", samples, acf_file, false)
#endif
{
	// Connect signal generator 1 sine
	src_sine_1.out(input_1);

	// Connect signal generator 2 sine
	src_sine_2.out(input_2);

	// Connect signal generator 3 sine
	src_sine_3.out(input_3);
	
	// Connect Mixer to add the sine signals together
	mix.in(input_1);
	mix.in(input_2);
	mix.in(input_3);
	mix.out(mix_out);

	// Split the mixed signal in 2 
	fork.in(mix_out);
	fork.out(monitor_in);
	
	// Monitor of mixed input result
	monitor_mix.in(monitor_in);

#ifdef SC_ARCHITECTURE

	pArch = new Arch("Arch", samples);
	fork.out(pArch->inAdapt);

#else
	// Functional routing

	fork.out(algo_in);

	pNSDF = new NSDF<type_T, WINDOW>("NSDF");

	pNSDF->in(algo_in);
	pNSDF->out(output);
	pNSDF->acf(acf_out);

	// Monitor of filtered output result
	monitor_ref.in(output);	
	monitor_acf.in(acf_out);
#endif


}
