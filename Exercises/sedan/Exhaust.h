#ifndef EXHAUST_H
#define EXHAUST_H
//BEGIN Exhaust.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See sedan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(Exhaust) {
  SC_HAS_PROCESS(Exhaust);
  Exhaust(sc_module_name nm);
  void Exhaust_thread(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: Exhaust.h,v 1.4 2004/04/15 17:44:21 dcblack Exp $
