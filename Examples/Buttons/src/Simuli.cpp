//----------------------------------------------------------------------------------------------
// Simuli.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Simulate button for test debouncing of input detector

#include "Simuli.h"

#define TS_LOGIC_0	SC_LOGIC_0
#define TS_LOGIC_1	SC_LOGIC_1

Simuli::Simuli(sc_module_name nm) : sc_module(nm)
{
	void SimulateNoice(void);
    SC_THREAD(Simulate);
	sensitive << clk_in;
    dont_initialize();
}

void Simuli::SimulateNoise()
{
	SetValue(TS_LOGIC_1);
	wait(1000, SC_US);

	SetValue(TS_LOGIC_0);
	wait(1000, SC_US);

	SetValue(TS_LOGIC_1);
	wait(1000, SC_US);

	SetValue(TS_LOGIC_0);
	wait(1000, SC_US);
}

void Simuli::SetValue(sc_logic val)
{
	for (unsigned i = 0; i < N_BUTTONS; i++)
	{
		sim_out[i]->write(val);
	}
}


void Simuli::Simulate(void)
{
#if 0
	for (unsigned i=0; i!=10; i++) 
	{
		wait(10000, SC_US);
		sim_out->write(TS_LOGIC_1);

		wait(10000, SC_US);
		sim_out->write(TS_LOGIC_0);
	}
#else
	for (unsigned i=0; i!=10; i++) 
	{

//		SimulateNoise();
		SetValue(TS_LOGIC_1);
		wait(1001, SC_US);

		SetValue(TS_LOGIC_0);
		wait(999, SC_US);

		SetValue(TS_LOGIC_1);
		wait(1001, SC_US);

		SetValue(TS_LOGIC_0);
		wait(999, SC_US);

		SetValue(TS_LOGIC_1);
		wait(10000, SC_US);

		SetValue(TS_LOGIC_0);
		wait(10000, SC_US);
	}
#endif
}
