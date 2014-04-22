//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This example illustrates how to insert time delays into SC_METHODs.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "systemc.h"
#include "method_delay.h"

int sc_main(int argc, char* argv[]) {
  cout << "Elaborating" << endl;
  method_delay delay_i("delay_i");
  cout << "Simulating" << endl;
  sc_start(6*FIVE);
  cout << "INFO: method_delay COMPLETED" << endl;
  return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2003/11/06 18:51:18 dcblack Exp $
