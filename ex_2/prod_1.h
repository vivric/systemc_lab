// prod_1.h

#include "systemc.h"

SC_MODULE(prod_1) {
public:
	// ports declaration
	sc_in<bool> clk;
	sc_out<int> dat1;
	sc_out<bool> put;
	sc_in<bool> f_full;

	// internal signal, public to enable tracing
	sc_signal<bool> send;

private:
	// member variable
	int prod_data;

	// process declaration
	void producer();
	void send_trigger();

public:
	// constructor
	SC_CTOR(prod_1) {

		// register processes
		SC_THREAD(send_trigger);
		SC_THREAD(producer);
		sensitive << clk.pos();

		// initialize member variables & ports
		dat1.initialize(-1);
		put.initialize(false);
		prod_data = 1;
	}
};

