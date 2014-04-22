#ifndef MONITOR_H
#define MONITOR_H
//----------------------------------------------------------------------------------------------
// Monitor.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Monitor for debounce of input detector

#include <systemc.h>
#include "Defs.h"

class Monitor : public sc_module
{
public:
  
  sc_in<sc_logic > input[N_BUTTONS];		// Input interface

  SC_CTOR(Monitor);

  void Simulate();			// Thread to Monitor input
  
};

#endif
