#ifndef SEMAPHORE_EX_H
#define SEMAPHORE_EX_H
//BEGIN semaphore_ex.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   TO_BE_SUPPLIED
//
// DESIGN HIERARCHY
//   sc_main()
//   +- semaphore_ex_i
//    +- customer1_thread
//    +- customer2_thread
//    +- customer3_thread
//    +- customer4_thread
//    +- customer5_thread
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(semaphore_ex) {
  sc_time MINS;
  unsigned fills;
  sc_semaphore pump;
  sc_event e_change;
  SC_CTOR(semaphore_ex) : pump(2), MINS(1,SC_SEC), fills(35)
  {
    SC_THREAD(customer1_thread);
    SC_THREAD(customer2_thread);
    SC_THREAD(customer3_thread);
    SC_THREAD(customer4_thread);
    SC_THREAD(customer5_thread);
    SC_METHOD(monitor_method);
      sensitive << e_change;
  }

  // Process methods
  void customer1_thread(void);
  void customer2_thread(void);
  void customer3_thread(void);
  void customer4_thread(void);
  void customer5_thread(void);
  void monitor_method(void);

  // Helper methods
  void customer(char* who);
  void delay(sc_time t,int uncertainty);
  void note(char* who,char* message);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: semaphore_ex.h,v 1.3 2004/04/15 17:44:42 dcblack Exp $
