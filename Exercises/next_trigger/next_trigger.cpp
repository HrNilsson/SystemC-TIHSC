//BEGIN next_trigger.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "next_trigger.h"

void next_trigger_example::my_waiting_method(void) {
  if (my_state == DONE) sc_stop();
  count++;
  cout << "INFO: Entering my_method with STATE" << my_state
       << " with count == " << count
       << " at time " << sc_time_stamp() << "." 
       << std::endl;
  switch (my_state) {
    case STATE1:
      // Wait 1 ns similar to Verilog #1
      next_trigger(1,SC_NS);
      if (count == 2) { // visit this state twice
        count = 0;
        my_state = STATE2;
      }//endif
      break;
    case STATE2:
      // Wait 0 ns similar to Verilog #0 wait for next delta cycle
      next_trigger(SC_ZERO_TIME);
      if (count == 3) { // visit this state three times
        count = 0;
        my_state = STATE3;
      }//endif
      break;
    case STATE3:
      // Wait 20 milliseconds
      next_trigger(20,SC_MS);
      if (count == 2) { // visit this state twice
        count = 0;
        my_state = DONE;
      }//endif
      break;
  }//endswitch
  cout << "INFO:  Leaving my_method with STATE" << my_state
       << std::endl;
  return;
}//end my_waiting_method();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: next_trigger.cpp,v 1.3 2004/02/02 12:39:36 dcblack Exp $
