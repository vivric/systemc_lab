// prod_3.h

#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

// to make things easier readable ...
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

SC_MODULE(prod_3)
{
	public:
	// initiator socket to interconnect producer with FIFO
	simple_initiator_socket<prod_3> prod2fifo_socket;

	private:
	// event for communication between send_trigger() and producer() processes
	sc_event send_event;
	// event for informing about finished transaction
	sc_event response_event;


	// *******===============================================================******* //
	// *******                      member_functions, processes              ******* //
	// *******===============================================================******* //

	private:
	void producer();
	void send_trigger();


	// nb_transport_bw() - Nonblocking Transport Backward path
	//                    (for requests, to be called from FIFO to producer)
	public:
	tlm_sync_enum                            // returns status
	nb_transport_bw
	( tlm_generic_payload  &payload,         // ref to payload
	  tlm_phase            &phase,		 // ref to phase
	  sc_time              &delay_time       // ref to delay time
	);


	// *******===============================================================******* //
	// *******                             constructor                       ******* //
	// *******===============================================================******* //

	public:
	SC_CTOR(prod_3):
	    prod2fifo_socket("prod2fifo_socket")  // call constructor of prod2fifo_socket
	{
		// register nb_transport_bw function with sockets
		prod2fifo_socket.register_nb_transport_bw(this, &prod_3::nb_transport_bw);

		// registration of processes
		SC_THREAD(producer);
		SC_THREAD(send_trigger);


	}

};
