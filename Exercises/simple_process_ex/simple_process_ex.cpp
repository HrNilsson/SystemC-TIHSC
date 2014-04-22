#include "simple_process_ex.h"
void simple_process_ex::my_thread_process(void) {
  std::cout << "my_thread_process executed within "
            << name() 
            << std::endl;
}
