//BEGIN resolved_ex.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See resolved_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "resolved_ex.h"

void resolved_ex::master1_thread(void) {
  const sc_logic request(SC_LOGIC_0);
  request_sig.write(SC_LOGIC_Z);
  addr.write(ZZ);
  wait(SC_ZERO_TIME);
  for(;;) {
    // request
    while (ack0_sig == false) {
      while (request_sig.read() != SC_LOGIC_Z) {
        wait(request_sig.default_event());
      }
      request_sig.write(request);
      wait(1*t_1NS,request_sig.default_event());
      if (request_sig.read() != request) {
        request_sig.write(SC_LOGIC_Z);
        wait((rand()%5+1)*t_1NS);
      }
      wait(2*t_1NS,ack0_sig.default_event());
    }
    // transfer
    addr.write(rand()%128);
    wait(data.default_event());
    // release
    addr.write(ZZ);
    request_sig.write(SC_LOGIC_Z);
    while (ack0_sig.read() != false) {
      wait(ack0_sig.default_event());
    }
  }//endforever
}//end master1_thread()

void resolved_ex::master2_thread(void) {
  const sc_logic request(SC_LOGIC_1);
  request_sig.write(SC_LOGIC_Z);
  addr.write(ZZ);
  wait(SC_ZERO_TIME);
  for(;;) {
    // request
    while (ack0_sig == false) {
      while (request_sig.read() != SC_LOGIC_Z) {
        wait(request_sig.default_event());
      }
      request_sig.write(request);
      wait(1*t_1NS,request_sig.default_event());
      if (request_sig.read() != request) {
        request_sig.write(SC_LOGIC_Z);
        wait((rand()%5+1)*t_1NS);
      }
      wait(2*t_1NS,ack0_sig.default_event());
    }
    // transfer
    addr.write(rand()%128+128);
    wait(data.default_event());
    // release
    addr.write(ZZ);
    request_sig.write(SC_LOGIC_Z);
    while (ack1_sig.read() != false) {
      wait(ack1_sig.default_event());
    }
  }//endforever
}//end master_thread()

void resolved_ex::slave_thread(void) {
  static unsigned count = 0;
  ack0_sig.write(false);
  ack1_sig.write(false);
  wait(SC_ZERO_TIME);
  for(;;) {
    sc_logic request;
    // wait for a request
    request = request_sig.read();
    while (request == SC_LOGIC_Z || request == SC_LOGIC_X) {
      wait(request_sig.default_event());
      request = request_sig.read();
    }
    // acknowledge request
    if (request == SC_LOGIC_0) ack0_sig.write(true);
    else                       ack1_sig.write(true);
    // get address
    wait(addr.default_event());
    // return data
    data.write(addr.read());
    // release
    while (request_sig.read() != SC_LOGIC_Z) {
      wait(request_sig.default_event());
    }
    data.write(ZZ);
    ack0_sig.write(false);
    ack1_sig.write(false);
    count++;
    if (count == 10) {
      cout << "INFO: Processed 10 requests. Stopping." << endl;
      sc_stop();
      wait(SC_ZERO_TIME);
    }
  }//endforever
}//end slave_thread()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: resolved_ex.cpp,v 1.5 2004/02/15 11:21:46 dcblack Exp $
