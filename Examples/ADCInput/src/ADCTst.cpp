SC_MODULE(ADCSource) 
{
	// Ports
	sc_in<sc_logic> clk_in;
	sc_out<sc_logic> busy_out;
	sc_out<sc_lv<SAMPLE_BITS> > data_out;

	// Local variables
	sc_uint<SAMPLE_BITS> counter;
	CirBuffer *m_CirBuffer;
 
	SC_CTOR(ADCSource);

	// Test source thread
	void ADCThread();

	void SampleReady(void);
};

ADCSource::ADCSource(sc_module_name nm): sc_module(nm), counter(0)
{
    SC_METHOD(SampleReady);
	sensitive << clk_in;
    dont_initialize();
}

void ADCSource::SampleReady(void)
{
	if (clk_in.read() == true)
	{
		sc_uint<SAMPLE_BITS> d = counter;
		counter += 1;
		data_out->write(d);
		busy_out->write(SC_LOGIC_1);
	}
	else
		busy_out->write(SC_LOGIC_0);
}
