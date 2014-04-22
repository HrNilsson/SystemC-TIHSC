//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See equalizer_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
using std::cout;
using std::endl;

#include <systemc.h>
#include "equalizer_ex.h"

unsigned errors = 0;
char* simulation_name = "equalizer_ex";

int sc_main(int argc, char* argv[]) {
  cout << "INFO: Elaborating "<< simulation_name << endl;
  //sc_set_time_resolution(1,SC_PS);
  //sc_set_default_time_unit(1,SC_NS);
  // Top-level channels
  sc_fifo<double> stimulus_fifo;
  sc_fifo<double> processed_fifo;
  // Top-level instance
  equalizer_ex equalizer_ex_i("equalizer_ex_i");
    equalizer_ex_i.raw_fifo_ip(stimulus_fifo);
    equalizer_ex_i.equalized_fifo_op(processed_fifo);
  cout << "INFO: Simulating "<< simulation_name << endl;
  sc_start();
  cout << "INFO: Post-processing "<< simulation_name << endl;
  cout << "INFO: Simulation " << simulation_name
       << " " << (errors?"FAILED":"PASSED")
       << " with " << errors << " errors"
       << endl;
  return errors?1:0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.2 2004/05/05 19:46:21 dcblack Exp $
