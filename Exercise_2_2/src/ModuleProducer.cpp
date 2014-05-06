#include "ModuleProducer.h"

using namespace std;

void ModuleProducer::Producer_th() {
	TCPHeader tcpHead;

	tcpHead.SequenceNumber = 0;
	while (1) {
		wait(rand()%9 + 2, SC_MS);
		tcpHead.SequenceNumber++;
		out[0]->write(&tcpHead);
		out[1]->write(&tcpHead);
	}
}

