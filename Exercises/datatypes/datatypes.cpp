//BEGIN datatypes.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   Examples of various data types in use.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define SC_INCLUDE_FX
#include <systemc.h>
#include <string>
#include <bitset>

using std::cout;
using std::endl;
using std::string;
using std::bitset;

int main(int argc, char* argv[]) {
  cout << "INFO: Starting datatypes" << endl;

  // Efficient native C++ data types
  int               spark_offset;         // Adjustment for ignition
  unsigned          repairs = 0;          // Count repair incidents
  unsigned long     mileage;              // Miles driven since manufacture
  short int         speedometer;          // 0..120 MPH
  float             temperature;          // Engine thermostat in degrees C
  double            time_of_last_request; // Capture time on each bus access
  string            license_plate;        // Text for license plate
  const bool        WARNING_LIGHT = true; // Status indicator
  enum Compass {SW,W,NW,N,NE,E,SE,S,nDir};// Direction of travel
  bitset<nDir>      obstacle;             // Indication of obstacles

  for (int heading=SW; heading<nDir; heading++) {
    cout << "Heading " << heading << endl;
  }//endfor
  if (int(temperature) % 2 == 1) license_plate = "Odd Temp";
  obstacle.set(NW);
  obstacle.set(E);
  unsigned long obstacles = obstacle.to_ulong();

  // SystemC integer data types
  sc_int<5>      seat_position = 3; // +/1 sixteen positions from neutral
  sc_uint<13>    days_SLOC(4000);   // Days Since Last Oil Change (SLOC)
  sc_biguint<40> revs_SLOC;         // Engine revolutions SLOC

  // SystemC boolean and multi-value data types
  // NOTE: sc_bit & sc_bv are probably better implemented with bool & bitset
  sc_bv<23>      system_status;     // Flags for each subsystem
  sc_logic       alarm_control;     // Initiate alarm (float idle or assert low)
  sc_lv<2391>    scan_chain;        // JTAG test points

  if (alarm) alarm_control = sc_logic_1;
  else       alarm_control = sc_logic_0;

  // SystemC fixed point data types
  sc_ufixed<12,7> driver_temp("98.6");
  const sc_fixed_fast<22,3> PI("3.141592654");
  sc_fix weird_circumference(13,9);
  weird_circumference = driver_temp * PI;
  cout << "sc_ufixed      driver_temp = " << driver_temp << endl;
  cout << "su_fixed_fast           PI = " << PI << endl;
  cout << "sc_fix weird_circumference = " << weird_circumference << endl;

  // Output all values
  cout << "obstacle=" << obstacle << endl;

  cout << "INFO: datatypes COMPLETED" << endl;
  return 0;

}//end main()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: datatypes.cpp,v 1.1 2003/11/06 18:39:05 dcblack Exp $
