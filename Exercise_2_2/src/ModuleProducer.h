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

SC_MODULE (ModuleProducer)
{
	sc_port<sc_fifo_out_if<TCPHeader *>,0> out;

	void Producer_th();

	SC_CTOR(ModuleProducer) {
		SC_THREAD(Producer_th);
	}
};

#endif
