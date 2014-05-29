//fifo_2.h

#ifndef __FIFO_2
#define __FIFO_2

#include "systemc.h"
#include "fifo_if.h"

class fifo_2 : public fifo_if, public sc_module 
{
	private:
	unsigned char *fifo_data;
	int write_addr, read_addr;
	int fill_level;
	unsigned char *data;
	const int fifo_size;  // in multiples of unsigned char

	void output_fifo_status();


	public:
	bool read_fifo(unsigned char *data, unsigned int &count);
	bool write_fifo(unsigned char *data, unsigned int &count);

	SC_CTOR(fifo_2):
		fifo_size(40)		   // initialize FIFO size
	{
		
		// initialization of member variables
		fifo_data = new unsigned char[fifo_size];
	
		write_addr = 0;
		read_addr  = 0;
		fill_level = 0;

	}

};

#endif

