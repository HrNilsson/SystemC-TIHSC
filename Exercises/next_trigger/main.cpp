//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "next_trigger.h"

int sc_main(int argc,char *argv[]) {
  cout << "INFO: Elaborating (constructing/binding)" << std::endl;
  next_trigger_example my_example("my_example");
  cout << "INFO: Starting simulation." << std::endl;
  sc_start(1,SC_SEC); // Simulate for 1 second
  cout << "INFO: Stopped simulating at " << sc_time_stamp() << "." << std::endl;
  cout << "INFO: next_trigger COMPLETED" << endl;
  return 0;
}//end sc_main()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2003/11/21 16:38:30 dcblack Exp $
