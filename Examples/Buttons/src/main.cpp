//----------------------------------------------------------------------------------------------
// main.cpp (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.09.07
//----------------------------------------------------------------------------------------------
// Debounce main for test bench testing button debouncer input detector
#include "Buttons.h"
#include "Top.h"

// Visual Studio version
int sc_main( int argc, char **argv)
{
	// Depricated since version SystemC version 2.2 is used
	//
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

#if defined(_MSC_VER)
	cout << "\n\tVisual Studio 8.0 - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

#if defined(__CYGWIN__)
	cout << "\n\tEclipse 3.3 and Cygwin - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

	// Instance of ringbuffer
	Top Top("DebouncerTest");

	sc_start( 1000, SC_MS );

	return 0;
}
