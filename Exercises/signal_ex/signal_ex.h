#ifndef SIGNAL_EX_H
#define SIGNAL_EX_H
//BEGIN signal_ex.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This example illustrates sc_signal evaluate-update behavior. There
//   are two variables (count & temp) and two signals (count_sig &
//   message_sig). Notice how ordinary variables update immediately;
//   whereas, signals require at least a delta-cycle delay (i.e.
//   wait(SC_ZERO_TIME);). Most of the action occurs in the process
//   signal_ex_thread, which reads and writes to these variable
//   and signals. The process signal_ex_method simply monitors the
//   associated events.
//
// DESIGN HIERARCHY
//   sc_main()
//   +- signal_ex_i
//    +- signal_ex_thread
//    +- signal_ex_method
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <string>
using std::string;

#include <systemc.h>

SC_MODULE(signal_ex) {
  enum color {BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE};
  // Local data variables
  int                  count;
  color                traffic_temp;
  string               message_temp;
  // Local channels
  sc_signal<int>       count_sig;
  sc_signal<color>     traffic_sig;
  sc_signal<string>    message_sig;
  // Constructor
  SC_CTOR(signal_ex)
  {
    SC_THREAD(signal_ex_thread);
    SC_METHOD(signal_ex_method);
      sensitive << count_sig
                << traffic_sig
                << message_sig;
  }
  void signal_ex_thread(void);
  void signal_ex_method(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: signal_ex.h,v 1.5 2004/04/15 17:44:53 dcblack Exp $
