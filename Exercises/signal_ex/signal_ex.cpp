//BEGIN signal_ex.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See signal_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "signal_ex.h"
#include <iostream>
using std::cout;
using std::endl;

void signal_ex::signal_ex_thread(void) {
// Moved the following to header file
//   // Declare variables
//   enum color {BLACK, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE};
//   int              count;
//   color            traffic_temp;
//   sc_string        message_temp;
//   sc_signal<int>   count_sig;
//   sc_signal<color> traffic_sig;
//   sc_signal<color> message_sig;

  // Initializing during 1st delta cycle
  cout << "NOTE: signal_ex_thread is initializing" << endl;
  count_sig.write(10);
  traffic_sig.write(BLACK);
  message_sig.write("Hello");
  count = 11;
  traffic_temp = RED;
  message_temp = "Whoa";
  wait(SC_ZERO_TIME);

  // 2nd delta cycle
  cout << "NOTE: signal_ex_thread is done initializing" << endl;
  count = 20;
  count_sig.write(count);
  cout << "----: count is " << count << " "
       << "count_sig is " << count_sig.read()
       << endl;
  cout << "NOTE: signal_ex_thread is waiting" << endl;

  // 3rd delta cycle
  wait(SC_ZERO_TIME);
  cout << "----: count is " << count << " "
       << "count_sig is " << count_sig.read()
       << endl;
  traffic_sig.write(traffic_temp = WHITE);
  cout << "----: traffic_temp is '" << traffic_temp << "' "
       << "traffic_sig '" << traffic_sig.read() << "'"
       << endl;
  message_sig.write(message_temp = "Rev your engines");
  cout << "----: message_temp is '" << message_temp << "' "
       << "message_sig '" << message_sig.read() << "'"
       << endl;

  // 4th delta cycle
  wait(SC_ZERO_TIME);
  // 5th delta cycle
  wait(SC_ZERO_TIME);
  cout << "NOTE: signal_ex_thread done" << endl;
}//end signal_ex_thread()

void signal_ex::signal_ex_method(void) {
  cout << "NOTE: signal_ex_method detected an EVENT!" << endl;
  cout << "----: count is " << count << " "
       << "and count_sig is " << count_sig.read() << endl;
  cout << "----: traffic_temp is " << traffic_temp << " "
       << "and traffic_sig " << traffic_sig.read() << endl;
  cout << "----: message_temp is '" << message_temp << "' "
       << "and message_sig '" << message_sig.read() << "'"<< endl;
}//end signal_ex_method()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: signal_ex.cpp,v 1.5 2004/03/04 21:42:55 dcblack Exp $
