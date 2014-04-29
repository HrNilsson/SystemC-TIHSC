#include "simple_process_ex.h"

void simple_process_ex::my_thread_process1(void)
{
  std::cout << "my_thread_process executed within "
            << name() 
            << std::endl;
  int counter = 0;
  while(1)
  {
  	int_fifo.write(counter++);
  	wait(10,SC_MS);
  }
}

void simple_process_ex::my_thread_process2(void)
{
  std::cout << "my_thread_process 2 executed within "
		  << name()
		  << std::endl;

  while(1)
  {
  	std::cout << int_fifo.read() << std::endl;
  	wait(10,SC_MS);
  }
}

void simple_process_ex::my_method(void)
{
	std::cout << "my_method executed within "
			  << name()
			  << std::endl;
}
