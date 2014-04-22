//BEGIN buffer_ex.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See buffer_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "buffer_ex.h"
#include <iostream>
using std::cout;
using std::endl;

void buffer_ex::buffer_ex_thread(void) {
  const sc_time t_1NS(1,SC_NS);
  cout << "NOTE(buffer_ex_thread): Initializing" << endl;
  my_sig.write(1.1);
  my_buf.write(2.1);
  wait(t_1NS);
  cout << "NOTE(buffer_ex_thread): Rewriting" << endl;
  my_sig.write(1.1);
  my_buf.write(2.1);
  wait(t_1NS);
  cout << "NOTE(buffer_ex_thread): Changing" << endl;
  my_sig.write(1.2);
  my_buf.write(2.2);
  wait(t_1NS);
  cout << "NOTE(buffer_ex_thread): Done" << endl;
}//end buffer_ex_thread()

void buffer_ex::sig_method(void) {
  cout << "INFO: my_sig = " << my_sig.read() << " @ " << sc_time_stamp() << endl;
}//end sig_method()

void buffer_ex::buf_method(void) {
  cout << "INFO: my_buf = " << my_buf.read() << " @ " << sc_time_stamp() << endl;
}//end buf_method()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: buffer_ex.cpp,v 1.2 2004/02/02 12:30:04 dcblack Exp $
