#include "ModuleProducer.h"

using namespace std;

void ModuleProducer::Producer_th() {
	TCPHeader tcpHead;

	tcpHead.SequenceNumber = 1;
	while (1) {
		wait(rand()%9 + 2, SC_MS);
		tcpHead.SequenceNumber++;
		fifo_channel.write(tcpHead);
	}
}

