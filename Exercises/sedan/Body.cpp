//BEGIN Body.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See sedan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "Body.h"

// Constructor
Body::Body(sc_module_name nm)
: sc_module(nm),
  Wheel_FL("Wheel_FL"),
  Wheel_FR("Wheel_FR"),
  Wheel_RL("Wheel_RL"),
  Wheel_RR("Wheel_RR")
{
  cout << "INFO: Constructing instance " << name() << endl;
  SC_THREAD(Body_thread);
}//end Body()

void Body::Body_thread(void) {
  cout << "INFO: Ran Body_thread inside instance " << name() << endl;
}//end Body_thread()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: Body.cpp,v 1.3 2004/02/02 12:46:14 dcblack Exp $
