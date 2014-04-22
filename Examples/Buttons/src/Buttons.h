#ifndef BUTTONS_H
#define BUTTONS_H
//----------------------------------------------------------------------------------------------
// Buttons.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.11
//----------------------------------------------------------------------------------------------
// Buttons contains an implementation of a container of N Debouncer's
//
//---------------------------------------------------------------------------------------------

#include <systemc.h>

#include "Defs.h"
#include "Debounce.h"

class Buttons : public sc_module
{
public:

  // Input interface
  sc_in<bool> clk;						// Clock input
  sc_in<sc_logic > input[N_BUTTONS];	// Logical high (1) when button pressed
 
  // Output interface
  sc_out<sc_logic > output[N_BUTTONS];	// Output to signal button pressed

  Debounce *db[N_BUTTONS];

  SC_CTOR(Buttons) 
  {
	  for (unsigned i = 0; i < N_BUTTONS; i++)
	  {
		  char bnt[20];
		  sprintf(bnt, "Button%i", i+1);
		  db[i] = new Debounce(bnt);
		  db[i]->clk(clk);
		  db[i]->input(input[i]); 
		  db[i]->output(output[i]);
	  }
  }

};

#endif
