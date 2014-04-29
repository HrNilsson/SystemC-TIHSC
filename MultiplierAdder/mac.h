/*
 * mac.h
 *
 *  Created on: Apr 30, 2013
 *      Author: kbe
 */

#ifndef MAC_H_
#define MAC_H_
#include <systemc.h>

SC_MODULE (Mac)
{
	sc_in<int> a, b, c;
	sc_out<int> f;

	sc_signal<int> p;

	void multiply();
	void addition();

	SC_CTOR(Mac) {
		SC_METHOD(multiply);
		sensitive << a << b;
		SC_METHOD(addition);
		sensitive << p << c;
	}
};

#endif /* MAC_H_ */
