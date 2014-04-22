#ifndef GAS_STATION_H
#define GAS_STATION_H
//BEGIN gas_station.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   Simple example of use of events and sc_threads. Time not modeled.
//
// DESIGN HIERARCHY
//   sc_main()
//   +- gas_station_i
//    +- customer1_thread << e_filled
//    +- customer2_thread
//    +- attendant_method << e_request1, e_request2
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
using std::cout;
using std::endl;

#include <string>
#include <systemc.h>

SC_MODULE(gas_station) {

  // Local module data
  const    sc_time t_MIN;
  bool     m_filling; // state of attendant
  double   m_full1, m_full2;
  double   m_filltime;
  sc_event e_request1, e_request2;
  double   m_tank1, m_tank2;
  unsigned m_count1, m_count2, m_maxcount;
  sc_event e_filled;

  // Constructor
  SC_HAS_PROCESS(gas_station);
  gas_station(
    sc_module_name _name,
    double   full1=10.0,
    double   full2=11.1,
    double   filltime=1.8,
    unsigned maxcount=5
  ) :
    sc_module(_name),
    m_full1(full1),
    m_full2(full2),
    m_filltime(filltime),
    m_tank1(full1),
    m_tank2(full2),
    m_count1(0),
    m_count2(0),
    m_maxcount(maxcount),
    m_filling(false),
    t_MIN(1,SC_NS) // treat 1 minute = 1 nanosecond
  {
    // Note parameters
    cout << "INFO: Gas station named \"" << name() << "\"" << endl;
    cout << "INFO:   Customer1 has " << m_full1 << " gallon tank." << endl;
    cout << "INFO:   Customer2 has " << m_full2 << " gallon tank." << endl;
    cout << "INFO:   Attendant takes " << m_filltime << " minutes per gallon." << endl;
    cout << "INFO:   Maximum of " << m_maxcount << " fills per customer." << endl;
    // Gas station clients & servers
    SC_THREAD(customer1_thread);
      sensitive(e_filled);
    SC_THREAD(customer2_thread);
    SC_METHOD(attendant_method);
      sensitive << e_request1 << e_request2;
      dont_initialize();
  }//endconstructor gas_station

  // Declare processes
  void customer1_thread(void);
  void customer2_thread(void);
  void attendant_method(void);

  // Helper methods
  std::string hms(void); // helper to display time
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: gas_station.h,v 1.4 2004/04/15 17:39:55 dcblack Exp $
