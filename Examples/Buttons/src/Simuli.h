#ifndef SIMULI_H
#define SIMULI_H
//----------------------------------------------------------------------------------------------
// Simuli.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Simulate of button for test debouncing of input detector

#include <systemc.h>
#include "Defs.h"

class Simuli : public sc_module
{
public:
	
	sc_in<bool>		 clk_in;		// Clock input

	sc_out<sc_logic > sim_out[N_BUTTONS];		// Port button simulate out
 	
	SC_CTOR(Simuli);				// Simuli constuctor

	void Simulate();				// Simulation thread

	void SimulateNoise();

	void SetValue(sc_logic val);

};

#endif
