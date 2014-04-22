//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "turn_of_events.h"

int sc_main(int argc, char* argv[]) {
  turn_of_events turn_of_events_i("turn_of_events_i");
  sc_start();
  std::cout << "Exiting turn of events simulation" << std::endl;
  return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2003/11/06 20:04:56 dcblack Exp $
