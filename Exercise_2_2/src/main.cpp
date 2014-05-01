#include "ModuleSingle.h"
#include "ModuleDouble.h"

int sc_main(int argc, char* argv[])
{
	/*-----2.2.1-----*/
	/*
	  ModuleSingle moduleSingle("ModuleSingle");
	  sc_start(200, SC_MS);
	  return 0;
	*/

	/*-----2.2.2-----*/
	/*
	ModuleDouble moduleDouble("ModuleDouble");
    sc_start(100, SC_MS);
	return 0;
	*/

	/*-----2.3.1-----*/

	ModuleProducer producer("ModuleProducer");
	ModuleConsumer consumer("ModuleConsumer");
	sc_start(100, SC_MS);
	return 0;




}
