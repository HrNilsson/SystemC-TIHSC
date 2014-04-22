//BEGIN method_delay.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This example illustrates how to insert time delays into SC_METHODs.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iomanip>
#include "method_delay.h"

using std::cout;
using std::setw;
using std::endl;

const sc_time FIVE(5,SC_NS);

void method_delay::delay_method(void) {
  switch (state) {
    case INIT:
      cout << setw(5) << sc_time_stamp() << " Initializing" << endl;
      cout << "      Preparing to wait five" << endl;
      state = FIVE_1;
      next_trigger(FIVE);
      break;
    case FIVE_1:
      cout << setw(5) << sc_time_stamp() << " Delayed five" << endl;
      state = FIVE_2;
      cout << "      Preparing to wait five" << endl;
      next_trigger(FIVE);
      break;
    case FIVE_2:
      cout << setw(5) << sc_time_stamp() << " Delayed five" << endl;
      cout << "      Preparing to wait zero" << endl;
      state = ZERO_1;
      next_trigger(SC_ZERO_TIME);
      break;
    case ZERO_1:
      cout << setw(5) << sc_time_stamp() << " Delayed one delta cycle" << endl;
      cout << "      Preparing to wait zero" << endl;
      state = ZERO_2;
      next_trigger(SC_ZERO_TIME);
      break;
    case ZERO_2:
      cout << setw(5) << sc_time_stamp() << " Delayed one delta cycle" << endl;
      cout << "      Preparing to stop after five" << endl;
      state = STOP;
      next_trigger(FIVE);
      break;
    case STOP:
      cout << setw(5) << sc_time_stamp() << " Stopping" << endl;
      next_trigger(99*FIVE);
      sc_stop();
      break;
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: method_delay.cpp,v 1.2 2004/02/02 12:38:28 dcblack Exp $
