#include "ModuleConsumer.h"

using namespace std;

void ModuleConsumer::Consumer_th() {
	TCPHeader tcpHead;

	while (1) {
		tcpHead = fifo_channel.read();
		cout << sc_time_stamp() << " " << tcpHead.SequenceNumber << endl;
	}
}
