//BEGIN mutex_ex.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See mutex_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "mutex_ex.h"

void mutex_ex::parent_thread  (void) {
  char * me("Parent");
  sc_time fudge(SC_ZERO_TIME);
  wait(6*hrs); // start day at 6 am
  for(;;) {
    note(me,"Wake up");
    delay(2*hrs,fudge,30);
    if (family_car.trylock()) {
      note(me,"Drive to work");
      delay(1*hrs,fudge,30);
      family_car.unlock();
      note(me,"Begin to work");
      delay(3*hrs,fudge,5);
      if (family_car.trylock()) {
        note(me,"Go to lunch");
        delay(1*hrs,fudge,15);
        family_car.unlock();
      } else {
        note(me,"Eat in - gripe at kid");
        delay(1*hrs,fudge,15);
      }//endif
      note(me,"Return to work");
      delay(3*hrs,fudge,15);
      note(me,"Attempting to get car back");
      family_car.lock();
      note(me,"Drive home");
      delay(1*hrs,fudge,30);
      family_car.unlock();
    } else {
      note(me,"Take bus to work");
      delay(9*hrs,fudge,45);
      note(me,"Take bus home");
    }//endif
    note(me,"Do chores and eat supper");
    delay(2*hrs,fudge,30);
    if (family_car.trylock()) {
      note(me,"Drive to meeting");
      delay(3*hrs,fudge,30);
      note(me,"Drive to home");
      family_car.unlock();
    } else {
      note(me,"Take a walk");
      delay(3*hrs,fudge,10);
    }//endif
    note(me,"Watch TV");
    delay(1*hrs,fudge,5);
    note(me,"Go to bed");
    delay(7*hrs,fudge,30);
  }//endfor
}//end mutex_ex::parent_thread  ()

void mutex_ex::teen_thread(void) {
  char * me("Teen");
  sc_time fudge(SC_ZERO_TIME);
  wait(10*hrs); // start day at 10 am
  for(;;) {
    note(me,"Wake up");
    delay(2*hrs,fudge,30);
    if (family_car.trylock()) {
      switch(rand()%4) {
        case 0: note(me,"Drive to school"); break;
        case 1: note(me,"Drive to mall"); break;
        case 2: note(me,"Drive to friends house"); break;
        case 3: note(me,"Drive to work"); break;
      }//endswitch
      delay(2*hrs,fudge,60);
      note(me,"Return car");
      family_car.unlock();
    } else {
      switch(rand()%4) {
        case 0: note(me,"Do schoolwork"); break;
        case 1: note(me,"Earn money"); break;
        case 2: note(me,"Do chores"); break;
        case 3: note(me,"Party"); break;
      }//endswitch
      delay(2*hrs,fudge,60);
    }//endif
    note(me,"Sleep");
    delay(2*hrs,fudge,60);
  }//endfor
}//end mutex_ex::teen_thread()

#include <iostream>
#include <iomanip>
using std::cout;
using std::setw;
using std::setfill;
using std::fixed;
using std::setprecision;
using std::endl;

void mutex_ex::delay(sc_time t, sc_time& fudge, int uncertainty) {
    int r = rand() % uncertainty;
    // add previous fudge back in to make up for previous uncertainty
    t += fudge;
    // compute fudge for this time
    fudge = (r - uncertainty/2)/60.0*hrs;
    // calculate actual delay
    sc_time d = t - fudge;
    if (d < SC_ZERO_TIME) d = SC_ZERO_TIME; // cannot delay negative
//  // debug
//  cout << "NOTE: waiting " 
//       << fixed << setprecision(2) << d.to_seconds() << " hrs"
//       << endl;
    wait(d);
}//end mutex_ex::delay()

void mutex_ex::note(char* who,char* message) {
  double t = sc_time_stamp().to_seconds();
  long   s = int(t);
  unsigned  h = s % 12;
  unsigned  m = int((t - double(s))* 60.0);
  bool     am = (s % 24)<12;
  cout << "NOTE: " 
       << setw(2) << h << ":"
       << setw(2) << setfill('0') << m << " "
       << (am?"AM":"PM")  << " "
       << who << ": "
       << message 
       << endl;
}//end mutex_ex::note()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: mutex_ex.cpp,v 1.2 2004/02/02 12:39:28 dcblack Exp $
