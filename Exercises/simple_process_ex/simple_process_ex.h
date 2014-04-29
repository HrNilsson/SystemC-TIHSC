#ifndef SIMPLE_PROCESS_EX_H
#define SIMPLE_PROCESS_EX_H
#include <systemc.h>

SC_MODULE(simple_process_ex) {

  SC_CTOR(simple_process_ex) {
    SC_THREAD(my_thread_process1);
    SC_THREAD(my_thread_process2);
    SC_METHOD(my_method);

  }

  sc_fifo<int> int_fifo;

  void my_thread_process1(void);
  void my_thread_process2(void);
  void my_method(void);
};

#endif
