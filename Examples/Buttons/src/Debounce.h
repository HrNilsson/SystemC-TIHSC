#ifndef DEBOUNCE_H
#define DEBOUNCE_H
//----------------------------------------------------------------------------------------------
// Debounce.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Debounce button input detector to prevent "meta stability"
//
// This code is to illustrate a SystemC implementation for filter bouncing of a button toggle.
//
// The circuit shown below is implemented using 2 input flip-flops to prevent meta stability.
// That means when the input from the button is between 0 and 1 there can be situtations
// where the input and output from the first flip-flop is unknown. Using 2 flip-flops in a row
// will prevent this situation and the output fQ2 will always be known either 1 or 0.
// The Xor gate detects every time there is a change in the input.
// That is when the fQ2 signal differs from fQ3. The output from the Xor gate generates the chip
// enable to the last flip-flop in the change, that finaly will reflect the filtered value of
// button pressed.
//
//                                                                      FF4
//             FF1           FF2          FF3           Xor           --------
//           -------- fQ1  ------- fQ2  -------  fQ3   ------|        >     Q|----->
// Clk   ---->     Q|--+   >    Q|--    >    Q|--------||     |  fCE4 |      |  Output
//           |      |  |   |     |  |   |     |        ||      |------|CE    |
//           |      |  |   |     |  |   |     |   +----||     |       |      |
// Input --->|D     |  +---|D    |  +---|D    |   |    ------|      |-|D     |
//           --------      -------  |   -------   |                 | --------
//                                  +-------------+-----------------+
//
//---------------------------------------------------------------------------------------------

#ifndef SC_SYNTHESIS
#include <systemc.h>
#endif

class Debounce : public sc_module
{
public:

  // Input interface
  sc_in<bool> clk;						// Clock input
  sc_in<sc_logic> input;				// Logical high (1) when button pressed

  // Output interface
  sc_out<sc_logic> output;				// Output to signal button pressed

  // Internal signals between gates
  sc_signal<sc_logic> fQ1, fQ2, fQ3, fCE4;

  // Triggered when clock goes high
  void Process();

  SC_CTOR(Debounce) {

	// Register processes
   	SC_METHOD(Process);
   	sensitive_pos << clk;	
   	dont_initialize();
  }

};

#endif
