#ifndef MONITOR_H_
#define MONITOR_H_
//============================================================================
// Name        : Monitor.h
// Author      : Kim Bjerge
// Version     : 2. sep 2010
// Description : Example of a smart pitch detector design using templates
// 				 This is an untimed model
//============================================================================

/**
 * Template Parameters:
 * 	class T - specifies the data-type used within the Monitor
 * 	T must be a numeric type that supports:
 * 		operator==(const T&)
 * 		operator=(int)
 * 		operator+=(const T&)
 * 		operator*(const T&)
 * 
 *  Constructor parameters:
 * 		sc_module_name name - specifies instance name
 * 		T gain - input gain
 **/

template <class T, unsigned D = 1> 
class Monitor : public sc_module 
{
public:
	sc_fifo_in<T> in;
	
	SC_HAS_PROCESS(Monitor);
	
	Monitor(sc_module_name name, int samples, std::string file_name, bool stop = true) :
		sc_module(name),
		m_samples(samples),
		m_file_name(file_name),
		m_stop(stop)
	{
		for (unsigned i = 0; i < D; i++)
			delay[i] = 0;
		m_in = 0;
		m_out = D-1;
		SC_THREAD(DoDisplay);
	}
	
private:
	int m_samples;
	std::string m_file_name;
	bool m_stop;
	T delay[D];
	int m_in, m_out;
	
	void DoDisplay()
	{
		ofstream *output_file = new ofstream(m_file_name.c_str());
		if (!output_file) 
		{
			cerr << "ERROR: Problem opening " << m_file_name << " for output." << endl;
			return;
		}
		
		T result;
		int counter = 0;
		while (1)
		{
			// Monitor with delay
			delay[m_in] = in.read();
			m_in = (m_in + 1) % D;
			result = delay[m_out];
			m_out = (m_out + 1) % D;
			
			*output_file << result << endl;
			if (m_stop) cout << result << endl;
			if ((++counter >= m_samples) && (m_stop)) sc_stop();
		}	
	}
};

#endif /*MONITOR_H_*/
