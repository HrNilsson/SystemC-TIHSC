#ifndef EQUALIZER_EX_H
#define EQUALIZER_EX_H
//BEGIN equalizer_ex.h
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This example illustrates the use of specialized ports (Chapter 12)
//   to use event finders. It is brief and to the point.
//
// DESIGN HIERARCHY
//   sc_main()
//   +- equalizer_ex_i
//    +- equalizer_ex_PROCESS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <systemc.h>

SC_MODULE(equalizer_ex) {
  sc_fifo_in<double>  raw_fifo_ip;      
  sc_fifo_out<double> equalized_fifo_op;
  SC_CTOR(equalizer_ex) {
    SC_THREAD(equalizer_thread);
    sensitive << raw_fifo_ip.data_written();
  }
  void equalizer_thread(void);
};

#endif
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: equalizer_ex.h,v 1.4 2004/05/05 19:46:21 dcblack Exp $
