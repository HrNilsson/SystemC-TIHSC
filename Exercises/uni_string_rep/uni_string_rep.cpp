// BEGIN uni_string_rep.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This example illustrates various formats of SystemC's "unified
//   string representations".
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SC_INCLUDE_FX
#include <systemc.h>
#include <iomanip>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {

  cout << "INFO: Starting uni_string_rep" << endl;

  sc_numrep NR[] = {
    SC_NOBASE, SC_DEC, SC_BIN, SC_BIN_US, SC_BIN_SM, SC_OCT, SC_OCT_US, 
    SC_OCT_SM, SC_HEX, SC_HEX_US, SC_HEX_SM, SC_CSD
  };
  sc_int<5> INT[] = {
    -13,   -3,   -1,   0,   1,   3,   13
  };
  sc_fixed<7,3> FXD[] = {
    -13.3, -2.7, -1.0, 0.0, 1.0, 3.3, 13.7
  };
  sc_fixed<7,3> FSD[] = {
    "-13.3", "-2.7", "-1.0", "0.0", "1.0", "3.3", "13.7"
  };
  for (unsigned iTC = 0; iTC!=7; iTC++) {
    for (unsigned iNR=1; iNR!=12; iNR++) {
      cout 
        << "  "  << std::setw(4) << INT[iTC] 
        << " = " << NR[iNR]
        << ":"   << std::setw(8) << INT[iTC].to_string(NR[iNR],true)

        << "  "  << std::setw(4) << FXD[iTC] 
        << " = " << NR[iNR]
        << ":"   << std::setw(8) << FXD[iTC].to_string(NR[iNR],true)

        << "  "  << std::setw(4) << FSD[iTC] 
        << " = " << NR[iNR]
        << ":"   << std::setw(8) << FSD[iTC].to_string(NR[iNR],true)

        << std::endl;
    }//endfor
  }//endfor

  cout << "INFO: uni_string_rep COMPLETED" << endl;
  return 0;

}//end main()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: uni_string_rep.cpp,v 1.1 2003/11/06 18:39:05 dcblack Exp $
