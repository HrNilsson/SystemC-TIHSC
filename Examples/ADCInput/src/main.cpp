//BEGIN main.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ADCTop.h"

// Visual Studio version
int sc_main( int argc, char **argv)
{
	// Depricated since version SystemC version 2.2 is used
	//sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);


#if defined(_MSC_VER)
	cout << "\n\tVisual Studio 8.0 - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

#if defined(__CYGWIN__)
	cout << "\n\tEclipse 3.3 and Cygwin - build with SystemC Ver.:" SC_RELEASE_STRING << "\n\n";
#endif

	// Instance of ringbuffer
	ADCTop ADCTop("ADCTest");

	sc_start( 50000, SC_NS );

	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// END $Id: main.cpp,v 1.1 2004/01/17 04:30:06 dcblack Exp $
