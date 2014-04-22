//============================================================================
// Name        : Arch.cpp
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector  design using templates
//               Contains the top level design 
//				 at functional and architecture level
//============================================================================
#include "Arch.h"

// Name of monitor files
const std::string rtl_file("output_mix.txt");

//----------------------------------------------------------------------------
// Architecture implementation and test of pitch detector
//----------------------------------------------------------------------------
Arch::Arch(sc_module_name name,
				 int samples) :
	sc_module(name),
	inAdapt("inAdapt"),
	outAdapt("outAdapt"),
	clock("clock", 20, SC_NS), // 50 mHz
	sample_clock("sample_clock", 21, SC_US), // 48 kHz
	reset("reset"),
	in_data("in_data"),
	out_data("out_data"),
	instNSDFArch("NSDFArch"),
	monitor_rtl("monitor_rtl", samples, rtl_file, false),
	m_samples(samples)
{
	reset.write(false);
	
	// Input adapter that wraps the fifo fir input to signals
	inAdapt.clock(clock);
	inAdapt.reset(reset);
	inAdapt.sample_clock(sample_clock);
	inAdapt.out_data(in_data);
	
	// Timed architecture version of NSDF algorithm
	instNSDFArch.clock(clock);
	instNSDFArch.reset(reset);
	instNSDFArch.sample_clock(sample_clock);
	instNSDFArch.in_data(in_data);
	instNSDFArch.out_data(out_data);
		
	// Output adapter that wraps the fir signals to output fifo
	outAdapt.clock(clock);
	outAdapt.reset(reset);
	outAdapt.sample_clock(sample_clock);
	outAdapt.in_data(out_data);
	
	// Monitor of filtered output result from RTL level
	monitor_rtl.in(outAdapt);

	// Create tacefile
	tracefile = sc_create_vcd_trace_file("PitchDetector");
	if (!tracefile) cout << "Could not create trace file." << endl;
	else cout << "Created PitchDetector.vcd" << endl;

	// Set resolution of trace file to be in 1 NS
	tracefile->set_time_unit(1, SC_NS);

	sc_trace(tracefile, clock.signal(), "clock");
	sc_trace(tracefile, sample_clock.signal(), "sample_clock");
	sc_trace(tracefile, reset, "reset");
	sc_trace(tracefile, in_data, "in_data");
	sc_trace(tracefile, out_data, "out_data");
}
				 
Arch::~Arch()
{
 	sc_close_vcd_trace_file(tracefile);
 	cout << "Closed PitchDetector.vcd" << endl;
}
