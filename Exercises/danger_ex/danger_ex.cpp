//BEGIN danger_ex.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See danger_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "danger_ex.h"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
using std::setprecision;
#include <cmath>

void danger_ex::danger_ex_thread(void) {
  const double INF = 1.0e12; // arbitrary large number
  cout << setprecision(3);
  for(double x=-5;x!=5;x++) {
    for(double y=-5;y!=5;y++) {
      // Convert rectangular to polar coordinates
      r = x;
      if ( r != 0 && r != 1 ) r = r * r;
      if ( y != 0 ) r = r + y*y;
      if ( x == 0 ) a = INF; // avoid divide-by-zero
      else          a = atan(y/x);
      if ( r == 0 ) a = -INF;
      cout << "NOTE " << setw(2) << sc_time_stamp() << ": "
           << "x = "  << setw(3) << x << " "
           << "y = "  << setw(3) << y << " "
           << "r = "  << setw(3) << r << " ";
      if (a == INF)       cout << "+INF" << endl;
      else if (a == -INF) cout << "-INF" << endl;
      else                cout << "a = " << setw(3) << a;
      cout << endl;
      wait(t_1NS);
    }//endfor y
  }//endfor x
}//end danger_ex_thread()

void danger_ex::collide_ex_thread(void) {
  wait(18*t_1NS);
  cout << "INFO: Colliding" << endl;
  r.write(3.141592654);
  wait(t_1NS);
}//end collide_ex_thread()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: danger_ex.cpp,v 1.2 2004/02/02 12:33:01 dcblack Exp $
