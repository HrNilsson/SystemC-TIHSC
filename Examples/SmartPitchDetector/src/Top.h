#ifndef TOP_H_
#define TOP_H_
//============================================================================
// Name        : Top.cpp
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector design using templates
//               Contains the top level design 
//				 at functional and architecture level
//============================================================================

#define SC_INCLUDE_FX
#include <systemc.h>
#include "Defs.h"
#include "Source.h"
#include "Mixer.h"
#include "Fork.h"
#include "NSDFFunc.h"
#include "Monitor.h"
#include "Arch.h"

class Top : public sc_module
{
public:

	// Create fifo channels
	sc_fifo<type_T> input_1;
	sc_fifo<type_T> input_2;
	sc_fifo<type_T> input_3;
	sc_fifo<type_T> mix_out;
	sc_fifo<type_T> algo_in;
	sc_fifo<type_T> monitor_in;
	sc_fifo<type_T> output;
	sc_fifo<type_T> acf_out;
	
	// Signal generator 1 sine
	Source<type_T> src_sine_1;

	// Signal generator 2 sine
	Source<type_T> src_sine_2;

	// Signal generator 3 sine
	Source<type_T> src_sine_3; 
	
	// Mixer to add the sine signals together
	Mixer<type_T> mix;

	// Split the mixed signal in 2 
	Fork<type_T> fork;
	
	// Monitor of mixed input result
	Monitor<type_T,1> monitor_mix;

	NSDF<type_T, WINDOW> *pNSDF; 
		
	// Architecture model of smart pitch detector
#ifdef SC_ARCHITECTURE
	Arch *pArch;
#else
	// Monitor of NSDF output result
	Monitor<type_T,6> monitor_ref;
	Monitor<type_T,6> monitor_acf;
#endif
	
	SC_HAS_PROCESS(Top);
	Top(sc_module_name name);
};

#endif /*TOP_H_*/

