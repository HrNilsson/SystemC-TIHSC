#ifndef MUTEX_EX_H
#define MUTEX_EX_H
//BEGIN mutex_ex.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This simulates a parent and a teen sharing a limited
//   resource, the family car. Time is scaled in this simulation
//   so that one second is registered as an hour. Two helper
//   methods are used to simplify the model. delay() is used to
//   create a specific delay +/- some random number of minutes.
//
// DESIGN HIERARCHY
//   sc_main()
//   +- mutex_ex_i
//    +- parent_thread
//    +- teen_thread
//    +- note
//    +- delay
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(mutex_ex) {
  sc_mutex family_car;
  sc_time hrs;
  SC_CTOR(mutex_ex): hrs(1,SC_SEC) /* 1 ns = 1 hr */
  {
    SC_THREAD(parent_thread  );
    SC_THREAD(teen_thread    );
  }

  // Processes
  void parent_thread(void);
  void teen_thread(void);

  // Helper methods
  void delay(sc_time t, sc_time& miss, int uncertainty); // waits +/- mins
  void note(char* who,char* message); // display time & message
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: mutex_ex.h,v 1.3 2004/04/15 17:42:45 dcblack Exp $
