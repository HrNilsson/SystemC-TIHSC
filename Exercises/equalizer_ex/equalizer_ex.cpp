//BEGIN equalizer_ex.cpp
//# vim600:set sw=2 tw=0 fdm=marker:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See equalizer_ex.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// systemc
#include "equalizer_ex.h"

void equalizer_ex::equalizer_thread(void) {//{{{
  for(;;) { 
    double sample;
    double result;
    wait();
    raw_fifo_ip->nb_read(sample);
    // ...
    // process data
    // ...
    equalized_fifo_op->write(result);
  }//endforever
}//}}}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: equalizer_ex.cpp,v 1.3 2004/05/05 19:46:21 dcblack Exp $
