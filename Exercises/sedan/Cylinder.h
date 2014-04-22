#ifndef CYCLINDER_H
#define CYCLINDER_H
//BEGIN Cylinder.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See sedan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(Cylinder) {
  // Constructor
  SC_HAS_PROCESS(Cylinder);
  Cylinder(sc_module_name nm);
  // Processes
  void Cylinder_thread(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: Cylinder.h,v 1.4 2004/04/15 17:44:10 dcblack Exp $
