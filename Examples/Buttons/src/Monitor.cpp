//----------------------------------------------------------------------------------------------
// Monitor.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Monitor for debounce of input detector

#include "Monitor.h"

Monitor::Monitor(sc_module_name nm) : sc_module(nm)
{
    SC_METHOD(Simulate);
    sensitive << input[0];
    dont_initialize();
}

void Monitor::Simulate(void)
{
	cout << input[0]->read() << ", ";
}
