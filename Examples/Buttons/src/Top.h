#ifndef TOP_H
#define TOP_H
//----------------------------------------------------------------------------------------------
// Top.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Top test benche for debounce button input detector

#include <systemc.h>

#include "Simuli.h"
#include "Monitor.h"

#define CLK_PERIODE	1000		// CLK rate - periode in us

class Top : public sc_module
{
public:

	sc_clock clock;								// Sample clock

	sc_signal<bool> clk;						// Clock signal

	sc_signal<sc_logic > input1;				// Button input signal 1
	sc_signal<sc_logic > input2;				// Button input signal 2
	sc_signal<sc_logic > input3;				// Button input signal 3
	sc_signal<sc_logic > input4;				// Button input signal 4
	sc_signal<sc_logic > input5;				// Button input signal 5

	sc_signal<sc_logic > output1;				// Button output signal 1
	sc_signal<sc_logic > output2;				// Button output signal 2
	sc_signal<sc_logic > output3;				// Button output signal 3
	sc_signal<sc_logic > output4;				// Button output signal 4
	sc_signal<sc_logic > output5;				// Button output signal 5
	
	sc_signal<sc_logic > *input[N_BUTTONS];
	sc_signal<sc_logic > *output[N_BUTTONS];

	// Modules and Components 
	Simuli *pSimuli;
	Buttons *pButtons;
	Monitor *pMonitor;

	sc_trace_file *tracefile;

	SC_CTOR(Top);
	~Top();

	// Method that creates a test bench
	// for testing of the debouncher
	void CreateTestBench();

	void ClockSignal();

};

#endif
