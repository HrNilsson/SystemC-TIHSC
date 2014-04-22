//============================================================================
// Name        : Top.cpp
// Author      : Kim Bjerge
// Version     : 22. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized design using templates
//               Contains the top level design 
//				 at functional and architecture level
//============================================================================
#include "Top.h"

//----------------------------------------------------------------------------
// Architecture implementation and test of FIR filter
//----------------------------------------------------------------------------
ArchFir::ArchFir(sc_module_name name,
				 FirCoeff_if<double> *pCoeff,
				 int samples) :
	sc_module(name),
	inAdapt("inAdapt"),
	outAdapt("outAdapt"),
	clock("clock", 10, SC_NS),
	sample_clock("sample_clock", 23, SC_US),
	reset("reset"),
	in_data("in_data"),
	out_data("out_data"),
	/*
#if defined (__CYGWIN__)
	firRtl("firRtl"),
#else
*/
	firRtl("firRtl", "work.synfir"), // ModelSim
//#endif
	monitor_rtl("monitor_rtl", samples, rtl_file),
	pFirCoeff(pCoeff),
	m_samples(samples)
{

	reset.write(false);
	
	// Input adapter that wraps the fifo fir input to signals
	inAdapt.clock(clock);
	inAdapt.reset(reset);
	inAdapt.sample_clock(sample_clock);
	inAdapt.out_data(in_data);
	
	// Timed synthesis version of FIR filter
	firRtl.clock(clock);
	firRtl.reset(reset);
	firRtl.sample_clock(sample_clock);
	firRtl.in_data(in_data);
	firRtl.out_data(out_data);
	
	// Set Coefficients
	for (int i = 0; i < TABS; i++)
		coeffs[i].write(pFirCoeff->GetCoeffInt(i));
	
	firRtl.in_coef0(coeffs[0]);
	firRtl.in_coef1(coeffs[1]);
	firRtl.in_coef2(coeffs[2]);
	firRtl.in_coef3(coeffs[3]);
	firRtl.in_coef4(coeffs[4]);
	firRtl.in_coef5(coeffs[5]);
	firRtl.in_coef6(coeffs[6]);
	firRtl.in_coef7(coeffs[7]);
	firRtl.in_coef8(coeffs[8]);
	firRtl.in_coef9(coeffs[9]);
	firRtl.in_coef10(coeffs[10]);
	firRtl.in_coef11(coeffs[11]);
	firRtl.in_coef12(coeffs[12]);
	firRtl.in_coef13(coeffs[13]);
	firRtl.in_coef14(coeffs[14]);
	firRtl.in_coef15(coeffs[15]);
	firRtl.in_coef16(coeffs[16]);
	firRtl.in_coef17(coeffs[17]);
	firRtl.in_coef18(coeffs[18]);
	firRtl.in_coef19(coeffs[19]);
	firRtl.in_coef20(coeffs[20]);
	firRtl.in_coef21(coeffs[21]);
	firRtl.in_coef22(coeffs[22]);
	
	// Output adapter that wraps the fir signals to output fifo
	outAdapt.clock(clock);
	outAdapt.reset(reset);
	outAdapt.sample_clock(sample_clock);
	outAdapt.in_data(out_data);
	
	// Monitor of filtered output result from RTL level
	monitor_rtl.in(outAdapt);

	// Create tacefile
	tracefile = sc_create_vcd_trace_file("FirWave");
	if (!tracefile) cout << "Could not create trace file." << endl;

	// Set resolution of trace file to be in 1 NS
	tracefile->set_time_unit(1, SC_NS);

	sc_trace(tracefile, clock.signal(), "clock");
	sc_trace(tracefile, sample_clock.signal(), "sample_clock");
	sc_trace(tracefile, reset, "reset");
	sc_trace(tracefile, in_data, "in_data");
	sc_trace(tracefile, out_data, "out_data");
}
				 
ArchFir::~ArchFir()
{
 	sc_close_vcd_trace_file(tracefile);
 	cout << "Created FirWave.vcd" << endl;
}
				 
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
#ifdef SC_ARCHITECTURE
		monitor_ref("monitor_ref", samples, ref_file, false)
#else
		monitor_ref("monitor_ref", samples, ref_file)
#endif
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

#ifdef SC_ARCHITECTURE
	pArchFir = new ArchFir("ArchFir", pFirCoeff, samples);
	fork.out(pArchFir->inAdapt);
#endif
	
}
