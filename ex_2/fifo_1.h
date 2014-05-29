// fifo_1.h

#include "systemc.h"

SC_MODULE(fifo_1) {
private:
	// process declaration
	void do_read();
	void do_write();
	void set_flags();

	// member variables
	const int fifo_size;
  	int *fifo_data;
	sc_signal<unsigned int> read_count;
	sc_signal<unsigned int> write_count;

public:
	// ports declaration
	sc_in<bool> clk;
	sc_in<bool> wr;
	sc_in<int> data_in;
	sc_in<bool> rd;
	sc_out<int> data_out;
	sc_out<bool> full;
	sc_out<bool> empty;

	// member variable, public to enable tracing
  	unsigned int fill_level;

	// constructor
	SC_CTOR(fifo_1) : fifo_size(5) {

		// register processes

		SC_METHOD(do_read);
		sensitive<<clk.pos();

		SC_METHOD(do_write);
		sensitive<<clk.pos();

		SC_METHOD(set_flags);
		sensitive << read_count << write_count;

		// initialization of member variables/ports
		fifo_data = new int[fifo_size];
		read_count.write(0);
		write_count.write(0);

		full.initialize(false);
		empty.initialize(true);
		data_out.initialize(-1);
	}
};
