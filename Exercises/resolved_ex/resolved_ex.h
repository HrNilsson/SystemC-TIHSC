#ifndef RESOLVED_EX_H
#define RESOLVED_EX_H
//BEGIN resolved_ex.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   TO_BE_SUPPLIED
//
// DESIGN HIERARCHY
//   sc_main()
//   +- resolved_ex_i
//    +- master_thread
//    +- slave_thread
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(resolved_ex) {
  sc_signal_resolved request_sig;
  sc_signal<bool> ack0_sig;
  sc_signal<bool> ack1_sig;
  sc_signal_rv<8> addr, data;
  SC_CTOR(resolved_ex)
  : t_1NS(1,SC_NS)
  , ZZ("zzzzzzzz")
  {
    SC_THREAD(master1_thread);
    SC_THREAD(master2_thread);
    SC_THREAD(slave_thread);
  }
  void master1_thread(void);
  void master2_thread(void);
  void slave_thread(void);
  // Local constants
  const sc_time t_1NS;
  const sc_lv<8> ZZ;
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: resolved_ex.h,v 1.5 2004/04/15 16:40:26 dcblack Exp $
