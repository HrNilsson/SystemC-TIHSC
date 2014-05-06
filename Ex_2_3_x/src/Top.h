
#ifndef TOP_H_
#define TOP_H_

#include <systemc.h>
#include "Master.h"
#include "Slave.h"

SC_MODULE (Top)
{
	Master m;
	Slave s;


	SC_CTOR(Top): m("Master"), s("Slave")
	{
		// Connect things
		m.ready(s.ready);
		s.valid(m.valid);
		s.data(m.data);
		s.error(m.error);
		s.channel(m.channel);
	}

};


#endif
