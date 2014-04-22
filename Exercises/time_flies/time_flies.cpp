//BEGIN time_flies.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See time_flies.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <iomanip>
using std::cout;
using std::setw;
using std::endl;
#include "time_flies.h"

void time_flies::time_thread(void) {
  cout << "INFO: Time resolution is " << sc_get_time_resolution() << endl;
  const sc_time t_1FS(1,SC_FS);
  const sc_time t_1S(1,SC_SEC);
  const sc_time t_1HR(3600*t_1S);// computed time
  sc_time t_DELAY(t_1FS);
  // Delay by powers of ten and display the resulting time
  for (;t_DELAY<=2*t_1HR;t_DELAY*=10) {
    cout << "INFO: Delaying " << setw(7) << t_DELAY << " ";
    wait(t_DELAY);
    cout << "INFO: Time is " << sc_time_stamp() << "!" << endl;
  }//endfor
  for (t_DELAY=2*t_1HR;t_DELAY>=t_1FS;t_DELAY/=10) {
    cout << "INFO: Delaying " << setw(7) << t_DELAY << " ";
    wait(t_DELAY);
    cout << "INFO: Time now " << display_hms(sc_simulation_time()) << "!" << endl;
  }//endfor
  wait(SC_ZERO_TIME);
  cout << "INFO: wait(SC_ZERO_TIME)" << endl;
  cout << "INFO: Time still " << display_hms(sc_simulation_time()) << "!" << endl;
  #ifdef USE_STOP
  cout << "INFO: Simulation will stop at the current time." << endl;
  sc_stop();
  #else
  cout << "INFO: Simulation will now proceed to limit specified by sc_start()" << endl;
  cout << "----: which is \"the maximum simulation time allowed\"." << endl;
  #endif
}//end time_thread()

  string time_flies::display_hms(double t) {
  char str[100];
  string result;
  unsigned hours   = int(t / 3600.0);
  t -= 3600.0*hours;
  unsigned minutes = int(t / 60.0);
  t -= 60.0*minutes;
  double   seconds = t;
  sprintf(str,
           "%d hours %d minutes %f seconds",
           hours,
           minutes,
           seconds
         );
  result = str;
  return result;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: time_flies.cpp,v 1.7 2004/04/01 18:10:06 dcblack Exp $
