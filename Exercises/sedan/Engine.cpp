//BEGIN Engine.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See sedan.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "Engine.h"

// Constructor
Engine::Engine(sc_module_name nm)
: sc_module(nm),
  fuelmix_i("fuelmix_i"),
  exhaust_i("exhaust_i"),
  cyl_i1("cyl_i1"),
  cyl_i2("cyl_i2")
{
  cout << "INFO: Constructing instance " << name() << endl;
  SC_THREAD(Engine_thread);
}//end Engine constructor

void Engine::Engine_thread(void) {
  cout << "INFO: Ran Engine_thread inside instance " << name() << endl;
}//end Engine_thread()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: Engine.cpp,v 1.3 2004/02/02 12:46:14 dcblack Exp $
