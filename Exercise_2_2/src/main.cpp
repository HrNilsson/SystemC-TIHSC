#include "ModuleSingle.h"
#include "ModuleDouble.h"
#include "Top231.h"


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

	Top231 top231("Top231");
	sc_start(100, SC_MS);
	return 0;




}
