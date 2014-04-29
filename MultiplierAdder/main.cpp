/*
 * main.cpp
 *
 *  Created on: Apr 30, 2013
 *      Author: kbe
 */
#include <iostream>
using namespace std;

#include "top.h"

// SystemC main creating the top level module and starts simulation
int sc_main(int argc, char* argv[])
{
	  Top top("Top");
	  sc_start(200, SC_NS);
	  return 0;
}
