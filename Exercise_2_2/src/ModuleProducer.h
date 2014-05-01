#ifndef MODULE_PRODUCER_H_
#define MODULE_PRODUCER_H_
#include <systemc.h>

#define PACKET_SIZE 512
#define DATA_SIZE (PACKET_SIZE-20)

typedef struct
{
	sc_uint<16> SourcePort;
	sc_uint<16> DestinationPort;
	sc_uint<32> SequenceNumber;
	sc_uint<32> Acknowledge;
	sc_uint<16> StatusBits;
	sc_uint<16> WindowSize;
	sc_uint<16> Checksum;
	sc_uint<16> UrgentPointer;
	char Data[DATA_SIZE];
} TCPHeader;

//TODO..?

sc_fifo<TCPHeader> fifo_channel;

SC_MODULE (ModuleProducer)
{

	void Producer_th();

	SC_CTOR(ModuleProducer) {
		SC_THREAD(Producer_th);
	}
};

#endif /* MAC_H_ */
