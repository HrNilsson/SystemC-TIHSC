//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See mutex_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
using std::cout;
using std::endl;

#include <systemc.h>
#include "mutex_ex.h"

unsigned errors = 0;
char* simulation_name = "mutex_ex";

int sc_main(int argc, char* argv[]) {
  //sc_set_time_resolution(1,SC_PS);
  //sc_set_default_time_unit(1,SC_NS);
  mutex_ex mutex_ex_i("mutex_ex_i");
  cout << "INFO: Starting "<<simulation_name<<" simulation" << endl;
  sc_time max_sim(96,SC_SEC);
  sc_start(max_sim);
  cout << "INFO: Exiting "<<simulation_name<<" simulation" << endl;
  cout << "INFO: Simulation " << simulation_name
       << " " << (errors?"FAILED":"PASSED")
       << " with " << errors << " errors"
       << endl;
  return errors?1:0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2003/11/25 12:55:40 dcblack Exp $
