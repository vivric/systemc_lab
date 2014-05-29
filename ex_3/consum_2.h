// consum_2.h

#ifndef __CONSUM_2
#define __CONSUM_2

#include "systemc.h"
#include "fifo_if.h"

SC_MODULE(consum_2) {

	public:
	sc_port<fifo_if> consum2fifo_port;

	private:
	// event for communication between consumer() and fetch_trigger()
	sc_event fetch_event;


	// *******===============================================================******* //
	// *******                      member_functions, processes              ******* //
	// *******===============================================================******* //
	
	private:
	void consumer();
	void fetch_trigger();


	// *******===============================================================*******
	// *******                             constructor                       *******
	// *******===============================================================*******

	public:
	SC_CTOR(consum_2)
	{

		// registration of processes
		SC_THREAD(consumer);
		SC_THREAD(fetch_trigger);

	}
};

#endif


