//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See gas_station.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "gas_station.h"

unsigned errors = 0;
char* simulation_name = "gas_station";

int sc_main(int argc, char* argv[]) {

  sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

  sc_set_time_resolution(1,SC_NS);
  sc_set_default_time_unit(1,SC_NS);
  gas_station Charlies("Charlies",/*full1*/10,/*full2*/12,/*filltime*/1.5,/*maxfills*/10);
  cout << "INFO: Starting gas_station simulation" << endl;
  sc_start();
  cout << "INFO: Exiting gas_station simulation" << endl;
  cout << "INFO: Simulation " << simulation_name
       << " " << (errors?"FAILED":"PASSED")
       << " with " << errors << " errors"
       << endl;
  return errors?1:0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2003/11/21 16:38:30 dcblack Exp $
