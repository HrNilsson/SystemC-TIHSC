//BEGIN gas_station.cpp (systemc)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// See gas_station.h for more information. Also note references to
// figure in textbook indicated as parenthesized numbers.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "gas_station.h"
using std::cout;
using std::endl;

extern unsigned errors;

void gas_station::customer1_thread(void) {
  for (;;) {
    // Simulate gas tank emptying time
    wait((m_full1+rand()%int(m_full1*0.10))*t_MIN);
    // Force 25% of all fillups to be simultaneous
    // with other customers. This makes sure the
    // contention situation is handled correctly.
    if (rand()%4==1) wait(e_request2);
    cout << "INFO: " << name()
         << " Customer1 needs gas (1) at "
         << hms() << endl;
    m_tank1 = 0;
    // Request fillup from attendant and then
    // wait for acknowledging event.
    do {
      e_request1.notify(); // I need fillup! (2)
      wait(); // use static sensitivity
      // Somebody got filled
    } while (m_tank1 == 0); // Was it us?
    // We got filled
  }//endforever
}//end customer1_thread()

void gas_station::customer2_thread(void) {
  for (;;) {
    // Simulate gas tank emptying time
    wait((m_full2+rand()%int(m_full2*0.10))*t_MIN);
    cout << "INFO: " << name() 
         << " Customer2 needs gas (1) at "
         << hms() << endl;
    m_tank2 = 0;
    // Request fillup from attendant and then
    // wait for acknowledging event.
    do {
      e_request2.notify(); // I need fillup! (2)
      wait(e_filled); // use dynamic sensitivity
    } while (m_tank2 == 0);
  }//endforever
}//end customer2_thread()

void gas_station::attendant_method(void) {
  // ASSERTION: We got here due to either 
  //   (A) a request in progress
  // or
  //   (B) an event request from a new customer

  // Because this is an SC_METHOD, we maintain a small amount of
  // state, m_filling. Initially, we're not filling. Once we get
  // a fillup request, we choose who, initiate filling, and then
  // use dynamic sensitivity to delay by the amount of time it
  // takes to fill the indicated gas tank.
  if (!m_filling) {
    // Check customer 1 first (preferential selection)
    if (m_tank1 == 0 && m_count1 < m_maxcount) {
      cout << "INFO: " << name() 
           << " Filling tank1 (3) at " 
           << hms() << endl;
      next_trigger(m_filltime*m_full1*t_MIN);
      m_filling = true;
    // Check customer 2 only if no customer 1
    } else if (m_tank2 == 0 && m_count2 < m_maxcount) {
      cout << "INFO: " << name()
           << " Filling tank2 (3) at " 
           << hms() << endl;
      next_trigger(m_filltime*m_full2*t_MIN);
      m_filling = true;
    }//endif
  } else {
    // We reach here by timing out on filling the tank, so first update
    // the tank, counts and issue messages about this event for the
    // appropriate customer. Then notify everyone of the event (4)
    if (m_tank1 == 0 && m_count1 < m_maxcount) {
      m_tank1 = m_full1;
      m_count1++;
      cout << "INFO: " << name()
           << " Filled tank1 (4) at " 
           << hms() << endl;
    } else if (m_tank2 == 0 && m_count2 < m_maxcount) {
      m_tank2 = m_full2;
      m_count2++;
      cout << "INFO: " << name()
           << " Filled tank2 (4) at " 
           << hms() << endl;
    }//endif
    e_filled.notify(SC_ZERO_TIME); // We finished filling (4) & are available!
    m_filling = false; // go back to waiting
    // See if we need to stop the simulation
    if (m_count1 == m_maxcount && m_count2 == m_maxcount) {
      cout << "WARN: " << name()
           << " No more fuel at " 
           << hms() << endl;
      sc_stop();
    }//endif
  }//endif
}//end attendant_method()

#include <sstream>

std::string gas_station::hms(void) {
  std::ostringstream now;
  double mins(sc_simulation_time());
  unsigned days = int(mins/(24*60));
  mins -= days*24.0*60.0;
  unsigned hrs = int(mins/60);
  mins -= hrs*60.0;
  if (days)            now << days << " days ";
  if (days||hrs)       now << hrs  << " hrs ";
  now                      << mins << " mins";
  return now.str();
}//end hms()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: gas_station.cpp,v 1.4 2004/03/04 15:15:17 dcblack Exp $
