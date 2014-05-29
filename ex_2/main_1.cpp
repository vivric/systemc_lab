// main.cpp

#include "consum_1.h"
#include "prod_1.h"
#include "fifo_1.h"

int sc_main(int argc, char *argv[]) {
        // the following instruction generates aclock signal with clock named "clock"
        // with a period of 100 ns, a duty cycle of 50%, and a falling edge after 50 ns
	sc_clock clk("clock", 100, SC_NS, 0.5, 50, SC_NS, false);

        // fill in the required commands to instantiate and connect
        // producer, fifo and cosumer
	prod_1 produce("prd");
	sc_signal<int> produced_data;
	sc_signal<bool> write_sig;
	sc_signal<bool> full;
	sc_signal<bool> f_empty;
	sc_signal<int> dataout;
	sc_signal<bool> read_signal;
	
	produce.dat1(produced_data);
	produce.put(write_sig);
	produce.f_full(full);
	produce.clk(clk);

	fifo_1 fifo("fifo");
	
		
	fifo.data_in(produced_data);
	fifo.wr(write_sig);
	fifo.data_out(dataout);
	fifo.full(full);
	fifo.empty(f_empty);
	fifo.rd(read_signal);
	fifo.clk(clk);
	
	consum_1 consumer("consumer");	
	consumer.fifo_empty(f_empty);
	consumer.data_write(dataout);
	consumer.get_data(read_signal);
	consumer.clk(clk);

	

	// fill in code to generate traces that can be used to observe the
	// functionality of the model with the waveform viewer gtkwave
	 sc_trace_file *tf = sc_create_vcd_trace_file("traces");  
  sc_trace(tf, produced_data, "produced_data");
  sc_trace(tf, clk, "clock");
  sc_trace(tf, write_sig, "write_signal");
  sc_trace(tf, consumer.data_write, "data write");
  //sc_trace(tf, f_empty, "fifo empty");
  //sc_trace(tf, dataout, "data out");
  //sc_trace(tf, read_signal, "read signal");


	sc_time sim_dur = sc_time(5000, SC_NS);
	if (argc != 2) {
		cout << "Default simulation time = " << sim_dur << endl;
	} else {
		sim_dur = sc_time(atoi(argv[1]), SC_NS);
	}

	// start simulation
	sc_start(sim_dur);

	// fill in code to close the trace file
sc_close_vcd_trace_file(tf);

	return 0;
}

