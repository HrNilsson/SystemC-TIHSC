#ifndef DANGER_EX_H
#define DANGER_EX_H
//BEGIN danger_ex.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This example illustrates two issues, one of which is undetected
//   by SystemC.
//
// DESIGN HIERARCHY
//   sc_main()
//   +- danger_ex_i
//    +- danger_ex_thread
//    +- collide_ex_thread
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(danger_ex) {
  const sc_time t_1NS;
  sc_signal<double> x, y, r, a;
  SC_CTOR(danger_ex)
  : t_1NS(1,SC_NS)
  {
    SC_THREAD(danger_ex_thread);
    SC_THREAD(collide_ex_thread);
  }
  void danger_ex_thread(void);
  void collide_ex_thread(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: danger_ex.h,v 1.3 2004/04/15 17:38:29 dcblack Exp $
