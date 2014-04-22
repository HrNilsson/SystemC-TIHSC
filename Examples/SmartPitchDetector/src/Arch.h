#ifndef ARCH_H_
#define ARCH_H_
//============================================================================
// Name        : Arch.cpp
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector design using templates
//               Contains the top level design 
//				 at functional and architecture level
//============================================================================

#define SC_INCLUDE_FX
#include <systemc.h>
#include "Defs.h"
#include "NSDFArch.h"
#include "Monitor.h"
#include "InAdapter.h"
#include "OutAdapter.h"

#if 1
typedef sc_fixed_fast<32,16> type_T;
const std::string ref_file("output_fixed.txt");
#else	
typedef double type_T;
const std::string ref_file("output_double.txt");
#endif

class Arch : public sc_module
{
public:	
	// Input and output fifo adapters
	InAdapter<type_T, ALGO_BITS> inAdapt;
	OutAdapter<type_T, ALGO_BITS> outAdapt;
	
	// Creation of clock, sample_clock and signals
	sc_clock clock;
	sc_clock sample_clock;
	sc_signal<bool> reset;
	
	sc_signal<sc_int<ALGO_BITS> > in_data;		
	sc_signal<sc_int<ALGO_BITS> > out_data;
			
	// Timed version of NSDF architecture model
	NSDFArch instNSDFArch;
	
	// Monitor of filtered output result from RTL level
	Monitor<type_T> monitor_rtl;

	sc_trace_file *tracefile;
		
	SC_HAS_PROCESS(Arch);
	
	Arch(sc_module_name name,
			int samples);
	
	~Arch();

private:	
	int m_samples;
	
};

#endif /*ARCH_H_*/

