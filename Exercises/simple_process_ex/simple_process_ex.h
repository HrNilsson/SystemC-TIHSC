#ifndef SIMPLE_PROCESS_EX_H
#define SIMPLE_PROCESS_EX_H
#include <systemc.h>
SC_MODULE(simple_process_ex) {
  SC_CTOR(simple_process_ex) {
    SC_THREAD(my_thread_process);
  }
  void my_thread_process(void);
};
#endif
