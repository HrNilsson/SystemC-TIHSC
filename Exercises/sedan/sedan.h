#ifndef SEDAN_H
#define SEDAN_H
//BEGIN sedan.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This old sedan Jalopy code illustrates the several direct
//   techniques of instantiation. First, main simply instantiates
//   the top-level sedan. sedan illustrates the popular header
//   only submodule technique, while Engine & Body illustrate the
//   separate implementation approach.
//
// DESIGN HIERARCHY
//   sc_main() -- top-level direct
//   +- sedan_i -- direct header only
//    +- sedan_thread
//    +- Engine eng_i -- direct separate implementation
//    |  +- FuelMix fuelmix_i
//    |  +- Exhaust exhaust_i
//    |  +- Cylinder cyl_i1
//    |  +- Cylinder cyl_i2
//    +- Body body_i -- direct separate implementation
//       +- Wheel wheel_FL
//       +- Wheel wheel_FR
//
// FILE HIERARCHY
//   sedan.x
//   +- $SYSTEMC/lib/systemc.a
//   +- main.cpp
//   +- sedan.cpp
//   |  +- sedan.h
//   |     +- Engine.h
//   |     +- Body.h
//   +- Engine.cpp
//   |  +- Engine.h
//   |     +- FuelMix.h
//   |     +- Exhaust.h
//   |     +- Cylinder.h
//   +- Body.cpp
//   |  +- Body.h
//   |     +- Wheel.h
//   +- FuelMix.cpp
//   |  +- FuelMix.h
//   +- Exhaust.cpp
//   |  +- Exhaust.h
//   +- Cylinder.cpp
//   |  +- Cylinder.h
//   +- Wheel.cpp
//      +- Wheel.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>
#include "Engine.h"
#include "Body.h"

SC_MODULE(sedan) {
  Engine Engine_i;
  Body Body_i;
  SC_CTOR(sedan)
  : Engine_i("Engine_i"),
    Body_i("Body_i")
  {
    cout << "INFO: Constructing instance " << name() << endl;
    SC_THREAD(sedan_thread);
  }
  void sedan_thread(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: sedan.h,v 1.3 2004/04/15 17:44:38 dcblack Exp $
