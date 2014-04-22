//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See time_flies.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
using std::cout;
using std::endl;
#include "time_flies.h"

int sc_main(int argc, char* argv[]) {

  sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

  sc_set_time_resolution(1,SC_FS);
  sc_set_default_time_unit(1,SC_SEC);
  cout << "Time resolution is " << sc_get_time_resolution() << endl;
  cout << "Default time unit is " << sc_get_default_time_unit() << endl;
  time_flies time_flies_i("time_flies_i");
  cout << "Starting time_flies simulation" << endl;
  sc_start();
  cout << "Exiting time_flies simulation." << endl;
  cout << "Simulator finished at " << time_flies_i.display_hms(sc_simulation_time());
  cout << endl;
  // Nothing to fail, so we exit with an unconditional OK
  return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.4 2004/04/01 18:10:06 dcblack Exp $
